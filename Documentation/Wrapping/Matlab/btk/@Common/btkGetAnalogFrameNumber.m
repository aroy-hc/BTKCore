function pfn = btkGetAnalogFrameNumber(h) %#ok
%BTKGETANALOGFRAMENUMBER Returns number of frame for the points.
% 
%  AFN = BTKGETANALOGFRAMENUMBER(H) returns the number of frame used in the analog's data.
%  The acquistion is represented by the handle H, obtained by the use of a 
%  btk* function.

%  Author: A. Barré
%  Copyright 2009- Biomechanical ToolKit (BTK).

% The following comment, MATLAB compiler pragma, is necessary to avoid 
% compiling this M-file instead of linking against the MEX-file.  Don't remove.
%# mex

error(generatemsgid('NotSupported'),'MEX file for BTKGETANALOGFRAMENUMBER not found');

% [EOF] btkGetAnalogFrameNumber.m