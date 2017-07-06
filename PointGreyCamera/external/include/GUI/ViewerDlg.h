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
	namespace GUI
	{
		/**
		 * @defgroup SpinnakerGUI Spinnaker GUI Classes
		 */

		/*@{*/

		/**
		 * @defgroup ViewerDlg_h Spinnaker GUI Viewer Dialog Class
		 */

		/*@{*/

		class SPINNAKER_API ViewerDlg
		{
		public:

			/**
			* Default constructor.
			*/
			ViewerDlg(void);


			/**
			 * Default destructor.
			 */
			~ViewerDlg(void);


			/**
			 * Connect ImageDrawingWindow to camera.
			 *
			 * @param pointer to a camera object
			 *
			 * @return boolean indicating whether the operation was successful
			 */
			bool Connect(Spinnaker::CameraPtr camera);


			/**
			 * Start image streaming.
			 *
			 */
			void StartStreaming();


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
			std::string GetTitle();


			/**
			 * Get the window title.
			 *
			 * @return string representing the title.
			 */
			void SetTitle(std::string title);


			/**
			 * Disconnect the ImageDrawingWindow from associated
			 * camera object.
			 *
			 */
			void Disconnect();


			/**
			 * Get a boolean indicating whether Window is connected to a camera object.
			 *
			 * @return boolean indicating connection status.
			 */
			bool IsConnected();


			/**
			 * Show the ImageDrawingWindow.
			 *
			 */
			void Open();


			/**
			 * Hide the ImageDrawingWindow.
			 *
			 */
			void Close();
		protected:

	#ifdef GUIFrame_GTK
			Spinnaker::GUI_GTKmm::Viewer* m_pGTKViewer;
	#else
			Spinnaker::GUI_WPF::ImageDrawingWindow* m_pWPFViewer;
	#endif
		};

		/*@}*/

		/*@}*/
	}
}