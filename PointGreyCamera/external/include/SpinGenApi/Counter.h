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
\brief    Definition of a simple Counter class
\ingroup Spinnaker_GenApi_PublicImpl
*/

#ifndef SPINNAKER_GENAPI_COUNTER_H
#define SPINNAKER_GENAPI_COUNTER_H

namespace Spinnaker
{

	namespace GenApi {

		class Counter
		{
		public:
			Counter() : m_value(0)
			{
			}

			unsigned int GetValue() const
				{ return m_value; }

			unsigned int operator++() // prefix
			{
				return ++m_value;
			}

			unsigned int operator++(int) // postfix
			{
				return m_value++;
			}

			unsigned int operator--(int) // postfix
			{
				assert( m_value > 0);
				return m_value--;
			}

			unsigned int operator--() // prefix
			{
				assert( m_value > 0);
				return --m_value;
			}

			operator unsigned int()
			{
				return m_value;
			}

			bool IsZero()
			{
				return m_value == 0;
			}

		private:
			unsigned int m_value;
		};
	}
}

#endif // SPINNAKER_GENAPI_COUNTER_H

