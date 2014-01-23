/* MainWindow.h
 *
 * Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
 *
 * This file is part of Melange.
 *
 * Melange is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Melange is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QMainWindow>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QLineEdit>
#include "audio-adaptor.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	QComboBox* m_playoutDeviceCombox;
	QComboBox* m_recordingDeviceCombox;
	QWidget* m_centralWidget;
	QFormLayout m_audioDeviceLayout;
	QVBoxLayout m_mainLayout;
	QHBoxLayout m_layoutMicTest;
	QHBoxLayout m_layoutMakeCall;
	QPushButton* m_pushBtnTestSpeaker;
	QPushButton* m_pushBtnTestMicrophone;
	QPushButton* m_pushBtnMakeCall;
	QLineEdit* m_textEditAddress;
	QProgressBar* m_barTestMicro;	
	AudioAdaptor m_audioAdaptor;
	QTimer* m_timerVolumeCheck;
	QWidget* m_widgetMicTest;
	QWidget* m_widgetMakeCall;
	bool m_bIsMicTesting;
	bool m_bIsActiveCall;
	
public:
	MainWindow();
	virtual ~MainWindow();
	
public slots:
	void on_playout_combobox_index_changed(int index);
	void on_recording_combobox_index_changed(int index);
	void on_timeout_fired();
	void on_pushbtn_test_speaker_pressed();
	void on_pushbtn_test_mic_pressed();
	void on_pushbtn_make_call_pressed();
};
