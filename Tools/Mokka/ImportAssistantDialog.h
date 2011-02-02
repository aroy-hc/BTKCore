/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2011, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ImportAssistantDialog_h
#define ImportAssistantDialog_h

#include "ui_ImportAssistantDialog.h"

#include <QDialog>
#include <QString>

class ImportAssistantDialog : public QDialog, public Ui::ImportAssistantDialog
{
  Q_OBJECT
  
public:
  ImportAssistantDialog(QWidget* parent = 0);
  void clear(const QString& dir);
  QStringList filenames() const;
  
public slots:
  void setAcquisitionSystem(int index);
  void openMotionTrajectoryFileDialog();
  void openMotionAnalogFileDialog();
  void openMotionForcePlatformFileDialog();
  void openMotionOrthotrackFileDialog();
  void openEliteTrajectoryFileDialog();
  void openEliteForcePlatformFileDialog();
  void openEliteEMGFileDialog();
  void openEliteAngleFileDialog();
  void openEliteMomentFileDialog();
  void openElitePowerFileDialog();
  
private:
  void openFileDialog(const QString& filter, QLineEdit* lineEdit);
  
  QString m_Directory;
};
#endif // ImportAssistantDialog_h