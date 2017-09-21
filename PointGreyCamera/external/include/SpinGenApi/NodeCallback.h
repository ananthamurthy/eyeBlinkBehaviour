//=============================================================================
// Copyright © 2016 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of 
// Point Grey Research, Inc. ("Confidential Information"). You shall not
// disclose such Confidential Information and shall use it only in 
// accordance with the terms of the "License Agreement" that you 
// entered into with PGR in connection with this software.
//
// UNLESS OTHERWISE SET OUT IN THE LICENSE AGREEMENT, THIS SOFTWARE IS 
// PROVIDED ON AN “AS-IS” BASIS AND POINT GREY RESEARCH INC. MAKES NO 
// REPRESENTATIONS OR WARRANTIES ABOUT THE SOFTWARE, EITHER EXPRESS 
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OR 
// CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR 
// NON-INFRINGEMENT. POINT GREY RESEARCH INC. SHALL NOT BE LIABLE FOR ANY 
// DAMAGES, INCLUDING BUT NOT LIMITED TO ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, PUNITIVE, OR CONSEQUENTIAL DAMAGES, OR ANY LOSS OF PROFITS, 
// REVENUE, DATA OR DATA USE, ARISING OUT OF OR IN CONNECTION WITH THIS 
// SOFTWARE OR OTHERWISE SUFFERED BY YOU AS A RESULT OF USING, MODIFYING 
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
/*!
\file
\brief   Implementation helpers for CNodeCallback
\ingroup Spinnaker_GenApi_PublicImpl

Defines a bunch of templates for creating callback-functors taking a INode pointer
and returning void.

\note does not work with all STL containers, i.e. std::map

*/

#ifndef SPINNAKER_GENAPI_NODECALLBACK_H
#define SPINNAKER_GENAPI_NODECALLBACK_H
#include "INode.h"

namespace Spinnaker
{
	namespace GenApi
	{

		//! the type of callback
		typedef enum _ECallbackType
		{
			cbPostInsideLock = 1,   //!> callback is fired on leaving the tree inside the lock-guarded area
			cbPostOutsideLock = 2   //!> callback is fired on leaving the tree inside the lock-guarded area
		} ECallbackType;

		/**
		\brief callback body instance for INode pointers
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		class CNodeCallback
		{
		public:
			CNodeCallback(INode* pNode, ECallbackType CallbackType) :
				m_pNode(pNode),
				m_CallbackType(CallbackType)
			{}

			//! virtual destructor
			virtual ~CNodeCallback()
			{};

			//! fires the callback if th type is right
			virtual void operator()(ECallbackType CallbackType) const = 0;

			//! destroys the object
			virtual void Destroy() = 0;

			//! returns the node the callback is registered to
			INode* GetNode()
			{
				return m_pNode;
			}

			ECallbackType GetCallbackType()
			{
				return m_CallbackType;
			}

		protected:
			//! the node were the callback is installed
			INode* m_pNode;

			//! the type of the callback
			ECallbackType m_CallbackType;
		};




		/***************************************************************************/
		// C Functions as callbacks
		/***************************************************************************/

		/**
		\brief Container for a function pointer
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		template <class Function>
		class Function_NodeCallback : public CNodeCallback
		{
		public:
			//! Constructor
			Function_NodeCallback(INode* pNode, const Function& function, ECallbackType CallbackType) :
				CNodeCallback(pNode, CallbackType),
				m_pFunction(function)
			{}

			//! execute operation: call the function
			virtual void operator()(ECallbackType CallbackType) const
			{
				if (m_pFunction && m_CallbackType == CallbackType)
					m_pFunction(m_pNode);
			}

			//! destroys teh object
			virtual void Destroy()
			{
				delete this;
			}

		private:
			//! the callback function
			const Function m_pFunction;

			//! no assignment operator
			Function_NodeCallback& operator=(Function_NodeCallback&);
		};

		/*-----------------------------------------------------------------------------*/

		/**
		\brief make a new callback object for C functions
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		template <class Function>
		CNodeCallback *make_NodeCallback(INode* pNode, Function function, ECallbackType CallbackType)
		{
			return static_cast<CNodeCallback*>(new Function_NodeCallback<Function>(pNode, function, CallbackType));
		}

		/*-----------------------------------------------------------------------------*/


		/**
		\brief Register a C-function as a callback
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		template<class Function>
		intptr_t Register(INode* pNode, Function f, ECallbackType CallbackType = cbPostInsideLock)
		{
			CNodeCallback *pCallback(make_NodeCallback(pNode, f, CallbackType));
			return pNode->RegisterCallback(pCallback);
		}


		/***************************************************************************/
		// C++ Member functions as callbacks
		/***************************************************************************/

		/**
		\brief Container for a member function pointer
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		template <class Client, class Member>
		class Member_NodeCallback : public CNodeCallback
		{
		public:
			//! Member function type
			typedef void (Client::*PMEMBERFUNC)(INode*);

			//! Constructor
			Member_NodeCallback(INode* pNode, Client& client, Member member, ECallbackType CallbackType) :
				CNodeCallback(pNode, CallbackType),
				m_Client(client),
				m_pMemberFunc(member)
			{}

			//! execute operation
			virtual void operator()(ECallbackType CallbackType) const
			{
				if (m_pMemberFunc && m_CallbackType == CallbackType)
					(m_Client.*m_pMemberFunc)(m_pNode);
			}

			//! destroys the object
			virtual void Destroy()
			{
				delete this;
			}

		private:
			//! The object the method function belongs to
			Client& m_Client;

			//! The method to call
			PMEMBERFUNC m_pMemberFunc;

			//! no assignment operator
			Member_NodeCallback& operator=(Member_NodeCallback&);
		};

		/*-----------------------------------------------------------------------------*/

		/**
		\brief make a new callback object for member functions
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		template <class Client, class Member>
		CNodeCallback *make_NodeCallback(INode* pNode, Client& client, Member member, ECallbackType CallbackType)
		{
			return static_cast<CNodeCallback*>(new Member_NodeCallback<Client, Member>(pNode, client, member, CallbackType));
		}

		/*-----------------------------------------------------------------------------*/

		/**
		\brief Register a C++-member function a callback
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		template<class Client, class Member>
		intptr_t Register(INode* pNode, Client &c, Member m, ECallbackType CallbackType = cbPostInsideLock)
		{
			CNodeCallback *pCallback(make_NodeCallback(pNode, c, m, CallbackType));
			return pNode->RegisterCallback(pCallback);
		}


		//! Unregistering callback by handle
		// definition in Node.cpp
		SPINNAKER_API void Deregister(GenApi::CallbackHandleType pCallbackInfo);

	}
}

#endif // SPINNAKER_GENAPI_NODECALLBACK_H
