//=============================================================================
// Copyright © 2015 Point Grey Research, Inc. All Rights Reserved.
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

#pragma warning(push)
#pragma warning(disable : 4275) //non dll-interface class 'Gtk::VBox' used as base for dll-interface class
#pragma warning(disable : 4250) // warning C4250: inherits 'Gtk::Object::Gtk::Object::destroy_notify_' via dominance   This kills all gtk warnings. For some reason have to put it outsite of #pragma warning(push)
#pragma once
#include "Spinnaker.h"

namespace Spinnaker
{
	namespace GUI_GTKmm
	{
		/**
		 * @defgroup SpinnakerGUIGTKmm Spinnaker GUI GTKmm Factory Class
		 */

		/*@{*/

		/**
		 * @defgroup PropertyGridWidget_h Spinnaker GUI GTKmm Property Grid Widget Class
		 */

		/*@{*/

		class SPINNAKER_API PropertyGridWidget : public Gtk::VBox
		{
			public:

				/**
				* Default constructor.
				*/
				PropertyGridWidget(void);


				/**
				* Default destructor.
				*/
				~PropertyGridWidget(void);


				/**
				 * Connect the PropertyGridWidgetWindow to a Camera object.
				 *
				 * @return boolean indicating whether the operation was successful
				 */
				bool Connect(Spinnaker::CameraPtr camera);


				/**
				 * Connect the PropertyGridWidgetWindow to a NodeMap object.
				 *
				 * @return boolean indicating whether the operation was successful
				 */
				bool Connect(Spinnaker::GenApi::INodeMap& nodeMap);

				/**
				 * Disconnect the PropertyGridWidgetWindow from associated
				 * nodemap object.
				 *
				 */
				void Disconnect();


				/**
				 * Get a boolean indicating whether PropertyGridWidgetWindow is connected to a camera object.
				 *
				 * @return boolean indicating connection status.
				 */
				bool IsConnected();


				/**
				 * Immediately refresh all features listed in PropertyGridWidget.
				 *
				 */
				void Refresh();


				/**
				 * Get the window title.
				 *
				 * @return string representing the title.
				 */
				Glib::ustring GetID();


				/**
				 * Set the window title.
				 *
				 * @param string representing the title.
				 */
				void SetID(Glib::ustring id);


				/**
				 * Show the PropertyGridWidgetWindow.
				 *
				 */
				void Open();


				/**
				 * Hide the PropertyGridWidgetWindow.
				 *
				 */
				void Close();

			protected:
				struct PropertyGridWidgetData;
				PropertyGridWidgetData* m_pPropertyGridWidgetData;
		};

		/*@}*/

		/*@}*/
	}
}
#pragma warning(pop)