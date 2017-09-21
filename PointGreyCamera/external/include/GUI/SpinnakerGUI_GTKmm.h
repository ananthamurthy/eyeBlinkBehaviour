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

#include <Spinnaker.h>
#include "Viewer.h"
#include "ViewerWidget.h"
#include "PropertyGridWidget.h"
#include "PropertyGrid.h"
#include "CameraSelection.h"
#include "CameraSelectionWidget.h"

namespace Spinnaker
{
	namespace GUI_GTKmm
	{
		/**
		 * @defgroup SpinnakerGUI Spinnaker GUI Classes
		 */

		/*@{*/

		/**
		 * @defgroup SpinnakerGUIGTKmm Spinnaker GUI GTKmm Factory Class
		 */

		/*@{*/

		class CameraControlProxy;

		class SPINNAKER_API GUIFactory
		{
			public:

				/**
				 * Default constructor.
				 */
				GUIFactory(void);


				/**
				 * Default destructor.
				 */
				~GUIFactory(void);



				/**
				 * Statically Get Camera Selection Window from GUI Factory
				 *
				 * @return A pointer to CameraSelectionWindow. User has ownership of this pointer.
				 */
				static CameraSelection* GetCameraSelectionDlg();


				/**
				 * Statically Get PropertyGridWindow from GUI Factory.
				 *
				 * @return A pointer to PropertyGridWindow. User has ownership of this pointer.
				 */
				static PropertyGrid* GetPropertyGridDlg();


				/**
				 * Statically Get Image Drawing Window
				 *
				 * @return A pointer to ImageDrawingWindow. User has ownership of this pointer.
				 */
				static Viewer* GetViewer();



				/**
				 * Connect GUI Factory to camera object
				 *
				 * @param pointer to a camera object
				 * @return boolean indicating whether operation was successful
				 */
				bool ConnectGUILib(Spinnaker::CameraPtr camera);


				/**
				 * Disconnect GUI Factory from camera object.
				 *
				 */
				void DisconnectGUILib();


				/**
				 * Get a boolean indicating whether GUI Factory is connected to a camera object.
				 *
				 * @return boolean indicating connection status.
				 */
				bool IsConnected(){return m_bisConnected;}


				/**
				 * Get number of dialogs contained in GUI Factory
				 *Need to ConnectGUILib() first, otherwise always return 0
				 * @return number of dialogs
				 */
				int GetNumDlgs();


				/**
				 * returns point of dialog at specific name list index in type of Gtk::Window*
				 *
				 * @param name index of dialog to be shown
				 */
				Gtk::Window* GetDlgByIndex(unsigned int index);


				/**
				 * returns point of dialog at specific name in type of Gtk::Window*
				 *
				 * @param name of dialog to be shown
				 */
				Gtk::Window* GetDlgByName(Glib::ustring dialogName);

				/**
				 * returns the top-most child in dialog
				 *
				 * @param name of dialog to be shown
				 */
				Gtk::Widget* GetDlgTopChild(Glib::ustring dialogName);


				/**
				 * Return number of controls contained in GUI Factory
				 *
				 * @return number of controls
				 */
				int GetNumCtrls();


				/**
				 * returns point of control at specific name list index in type of Gtk::Widget*
				 *
				 * @param name index of control to be shown
				 */
				Gtk::Widget* GetCtrlByIndex(unsigned int index);


				/**
				 * returns point of control at specific SFNCname in type of Gtk::Widget*
				 *
				 * @param SFNCname of control to be shown
				 */
				Gtk::Widget* GetCtrlBySFNCName(Glib::ustring controlName);


				/**
				 * returns point of control at specific name in type of Gtk::Widget*
				 *
				 * @param name of control to be shown
				 */
				Gtk::Widget* GetCtrlByName(Glib::ustring controlName);



				/**
				 * Get a list of dialog names
				 *
				 * @return string list of dialog names
				 */
				std::list<std::string> GetDialogNameList();

				/**
				 * Get a list of dialog titles
				 *
				 * @return string list of dialog titles
				 */
				std::list<std::string> GetDialogTitleList();

				/**
				 * Get dialog with specific name
				 *
				 * @param string holding dialog name
				 */
				std::list<std::string> GetControlNameList();


				/*Release all static instance of the API. This function must be called to remove the statically created PropertyGrid, CameraSelection, and viewer
				 *Note: This function won't destroy the controls created by user input XML, the user will have to call delete Spinnaker::GUI_GTKmm instance or Disconnect.
				 *If the user statically created components without declaring API instance, Release() must be called.
				 */
				static void Release();

			protected:
			//Signal handlers:
			sigc::connection m_GetCtrlConnection;
			bool m_bisConnected;
			Spinnaker::GenApi::INodeMap* m_map;
			static CameraSelection* m_CameraSelectionDialog;
			static Viewer* m_pViewer;
			static PropertyGrid* m_pPropertyGridDialog;
			CameraControlProxy* m_pCameraControlProxy;
		};

		/*@}*/

		/*@}*/
	}
}
