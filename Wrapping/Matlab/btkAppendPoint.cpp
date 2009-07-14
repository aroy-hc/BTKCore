/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009, Arnaud Barré
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

#include "btkMEXObjectHandle.h"
#include "btkMEXGetPoints.h"

#include <btkAcquisition.h>
#include <btkPoint.h>
#include <btkConvert.h>

// btkAppendPoint(h, type, label, values, residual, mask, description)
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if(nrhs < 4)
    mexErrMsgTxt("Minimum of four inputs required.");
  if (nlhs > 2)
   mexErrMsgTxt("Too many output arguments.");

  int vn = 0, mn = 0, rn = 0;

  if (!mxIsChar(prhs[1]) || mxIsEmpty(prhs[1]))
    mexErrMsgTxt("Point's type must be a non-empty string.");
  if (!mxIsChar(prhs[2]))
    mexErrMsgTxt("Point's label must be a non-empty string");
  if (!mxIsNumeric(prhs[3]) || mxIsEmpty(prhs[3]) || mxIsComplex(prhs[3]) || (mxGetN(prhs[3]) != 3))
    mexErrMsgTxt("Point's values must have a second dimension equals to 3.");
  vn = mxGetM(prhs[3]);
  if (nrhs >= 5)
  {
     if (!mxIsNumeric(prhs[4]) || mxIsEmpty(prhs[4]) || mxIsComplex(prhs[4]) || (mxGetN(prhs[4]) != 1))
    mexErrMsgTxt("Point's residual must have a second dimension equals to 1.");
    rn = mxGetM(prhs[4]);
  }
  if (nrhs >= 6)
  {
     if (!mxIsNumeric(prhs[5]) || mxIsEmpty(prhs[5]) || mxIsComplex(prhs[5]) || (mxGetN(prhs[5]) != 1))
    mexErrMsgTxt("Point's mask must have a second dimension equals to 1.");
    mn = mxGetM(prhs[5]);
  }
  if (((rn != vn) && (rn != 0)) || ((mn != vn) && (mn != 0)))
    mexErrMsgTxt("Point's data have not the same number of frames.");
  if (nrhs >= 7)
  {
    if (!mxIsChar(prhs[6]))
      mexErrMsgTxt("Point's description must be a string");
  }
  
  btk::Acquisition::Pointer acq = btk_MOH_get_object<btk::Acquisition>(prhs[0]);

  if (vn != acq->GetPointFrameNumber())
    mexErrMsgTxt("Frame number mismatching.");

  // label
  int strlen = (mxGetM(prhs[2]) * mxGetN(prhs[2]) * sizeof(mxChar)) + 1;
  char* label = (char*)mxMalloc(strlen);
  mxGetString(prhs[2], label, strlen);
  if (acq->FindPoint(label) != acq->EndPoint())
  {
    std::string err = "A point in the acquisition has already the label: '" + std::string(label) + "'.";
    mxFree(label);
    mexErrMsgTxt(err.c_str());
  }

  // type
  strlen = (mxGetM(prhs[1]) * mxGetN(prhs[1]) * sizeof(mxChar)) + 1;
  char* type = (char*)mxMalloc(strlen);
  mxGetString(prhs[1], type, strlen);
  btk::Point::Type t;
  if (strcmpi(type, "MARKER") == 0)
    t = btk::Point::Marker;
  else if(strcmpi(type, "ANGLE") == 0)
    t = btk::Point::Angle;
  else if(strcmpi(type, "FORCE") == 0)
    t = btk::Point::Force;
  else if(strcmpi(type, "MOMENT") == 0)
    t = btk::Point::Moment;
  else if(strcmpi(type, "POWER") == 0)
    t = btk::Point::Power;
  else if(strcmpi(type, "SCALAR") == 0)
    t = btk::Point::Scalar;
  else if(strcmpi(type, "REACTION") == 0)
    t = btk::Point::Reaction;
  else
  {
    std::string err = "Unknown point's type: '" + std::string(type) + "'.";    
    mexErrMsgTxt(err.c_str());
  }
  
  btk::Point::Pointer point = btk::Point::New(label, vn, t);
  mxFree(type);
  mxFree(label);

  memcpy(point->GetValues().data(), mxGetPr(prhs[3]) , mxGetNumberOfElements(prhs[3]) * sizeof(double));
  if (nrhs >= 5)
    memcpy(point->GetResiduals().data(), mxGetPr(prhs[4]) , mxGetNumberOfElements(prhs[4]) * sizeof(double)); 
  if (nrhs >= 6)
    memcpy(point->GetMasks().data(), mxGetPr(prhs[5]) , mxGetNumberOfElements(prhs[5]) * sizeof(double));
  if (nrhs >= 7)
  {
    int strlen = (mxGetM(prhs[6]) * mxGetN(prhs[6]) * sizeof(mxChar)) + 1;
    char* desc = (char*)mxMalloc(strlen);
    mxGetString(prhs[6], desc, strlen);
    point->SetDescription(desc);
    mxFree(desc);
  }

  acq->AppendPoint(point);

  // Return updated points
  btkMEXGetPoints(acq, nlhs, plhs);
};
