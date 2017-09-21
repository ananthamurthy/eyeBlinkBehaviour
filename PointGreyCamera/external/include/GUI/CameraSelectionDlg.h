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

namespace Spinnaker
{
	namespace GUI
	{
		/**
		 * @defgroup SpinnakerGUI Spinnaker GUI Classes
		 */

		/*@{*/

		/**
		 * @defgroup CameraSelectionDlg_h Spinnaker GUI Camera Selection Dialog Class
		 */

		/*@{*/

		class SPINNAKER_API CameraSelectionDlg
		{
			public:

				/**
				* Default constructor.
				*/
				CameraSelectionDlg(void);


				/**
				* Default destructor.
				*/

				~CameraSelectionDlg(void);

				/**
				 * Register callback function for double clicked event on listed devices in CameraSelectionWindow
				 *
				 * @param function pointer to double clicked event
				 */
				void RegisterDoubleClickedCallback(Spinnaker::GUI_WPF::ClickedEventCallback pCallBackFunc);


				/**
				 * Register callback function for single clicked event on listed devices in CameraSelectionWindow
				 *
				 * @param function pointer to single clicked event
				 */
				void RegisterSingleClickedCallback(Spinnaker::GUI_WPF::ClickedEventCallback pCallBackFunc);


				/**
				 * Rescan devices and refresh CameraSelectionWindow.
				 *
				 */
				void Refresh();


				/**
				 * Show the CameraSelectionWindow.
				 *
				 */
				void Open();


				/**
				 * Hide the CameraSelectionWindow.
				 *
				 */
				void Close();


				/**
				 * Set the window title.
				 *
				 * @param string representing the title.
				 */
				void SetTitle(std::string title);


				/**
				 * Get the window title.
				 *
				 * @return string representing the title.
				 */
				std::string GetTitle();

			private:

	#ifdef GUIFrame_GTK
				Spinnaker::GUI_GTKmm::CameraSelection* m_pGTKCameraSelection;
	#else
				Spinnaker::GUI_WPF::CameraSelectionWindow* m_pWPFCameraSelection;
	#endif
		};

		/*@}*/

		/*@}*/
	}
}