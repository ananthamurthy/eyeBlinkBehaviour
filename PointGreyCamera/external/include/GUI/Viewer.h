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
		 * @defgroup Viewer_h Spinnaker GUI GTKmm Viewer Class
		 */

		/*@{*/

		class ViewerWidget;
		class SPINNAKER_API Viewer
		{
		public:

			/**
			* Default constructor.
			*/
			Viewer(void);


			/**
			 * Default destructor.
			 */
			~Viewer(void);


			/**
			 * Connect ImageDrawingWindow to camera.
			 *
			 * @param pointer to a camera object
			 *
			 * @return boolean indicating whether the operation was successful
			 */
			bool Connect(Spinnaker::CameraPtr camera);


			/**
			 * Disconnect the ImageDrawingWindow from associated
			 * camera object.
			 *
			 */
			void Disconnect();


			/**
			 * Start image streaming.
			 *
			 */
			void StartStreaming();


			/**
			 * Get a boolean indicating whether Window is connected to a camera object.
			 *
			 * @return boolean indicating connection status.
			 */
			bool IsConnected(){return m_bIsConnected;};


			/**
			 * Stop image streaming.
			 *
			 */
			void StopStreaming();


			/**
			 * Set the window title.
			 *
			 * @param string representing the title.
			 */
			Glib::ustring GetID();

			/**
			 * Set the window title.
			 *
			 * @param string representing the title.
			 */
			void SetID(Glib::ustring id);


			/**
			*Get a new Viewer widget
			*@return a Gtk::Widget* pointer for Viewer
			*/
			ViewerWidget* GetWidget();


			/**
			 * Open the ImageDrawingWindow.
			 *
			 */
			void Open();

			/**
			 * Hide the ImageDrawingWindow.
			 *
			 */
			void Close();
		protected:
				struct ViewerData;
				ViewerData* m_pViewerData;
				bool m_bIsConnected;
		};

		/*@}*/

		/*@}*/
	}
}
