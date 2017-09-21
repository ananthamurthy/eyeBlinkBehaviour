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
		 * @defgroup CameraSelectionWidget_h Spinnaker GUI GTKmm Camera Selection Widget Class
		 */

		/*@{*/

		class SPINNAKER_API CameraSelectionWidget : public Gtk::VBox
		{
			public:

				/**
				 * Default constructor.
				 */
				CameraSelectionWidget(void);


				/**
				 * Default destructor.
				 */
				~CameraSelectionWidget(void);


				/**
				 * Callback signal for single clicked event on listed devices in CameraSelectionWidgetWindow
				 * The user needs to connect the signal to functions which have parameters of void pFunction (bool, Spinnaker::Camera*, Spinnaker::Interface*);
				 * @param bool isCameraClicked,  Spinnaker::Camera* camera (returns NULL is isCameraClicked == false), Spinnaker::Interface* interface(returns NULL is isCameraClicked == true)
				 */
				sigc::signal<void, bool, Spinnaker::CameraPtr*, Spinnaker::Interface*> signal_single_clicked();


				/**
				 * Callback signal for double clicked event on listed devices in CameraSelectionWidgetWindow
				 * The user needs to connect the signal to functions which have parameters of void pFunction (bool, Spinnaker::Camera*, Spinnaker::Interface*);
				 * @param bool isCameraClicked,  Spinnaker::Camera* camera (returns NULL is isCameraClicked == false), Spinnaker::Interface* interface(returns NULL is isCameraClicked == true)
				 */
				sigc::signal<void, bool, Spinnaker::CameraPtr*, Spinnaker::Interface*> signal_double_clicked();


				/**
				 * Callback signal for start or stop device clicked clicked event on listed devices in CameraSelectionWidgetWindow
				 * The user needs to connect the signal to functions which have parameters of void pFunction (Spinnaker::Camera*);
				 * @param Spinnaker::Camera* pCamera
				 */
				sigc::signal<void, Spinnaker::CameraPtr> signal_startstop_device_clicked();

				/**
				 * Callback signal for configure device clicked clicked event on listed devices in CameraSelectionWidgetWindow
				 * The user needs to connect the signal to functions which have parameters of void pFunction (Spinnaker::Camera*);
				 * @param Spinnaker::Camera* pCamera
				 */
				sigc::signal<void, Spinnaker::CameraPtr> signal_configure_device_clicked();


				/* Open the CameraSelectionWidgetWindow.
				 *
				 */
				void Open();


				/**
				 * Close the CameraSelectionWidgetWindow.
				 *
				 */
				void Close();


				/**
				 * Rescan devices and refresh CameraSelectionWidgetWindow.
				 *
				 */
				void Refresh();

				/**
				 * Set the Widget ID.
				 *
				 * @param Glib::ustring representing the title.
				 */
				void SetID(Glib::ustring id);


				/**
				 * Get the Widget ID.
				 *
				 * @return Glib::ustring representing the title.
				 */
				Glib::ustring GetID();

			protected:
				struct CameraSelectionWidgetData;
				CameraSelectionWidgetData* m_pCameraSelectionWidgetData;
				Spinnaker::CameraList m_allCameraList;
		};

		/*@}*/

		/*@}*/
	}
}
#pragma warning(pop)
