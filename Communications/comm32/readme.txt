COMM32.PAS
==========

Version 1.20

Comm32.pas is a simple Communications VC for Borland Delphi 2.0 which 
demonstrates the Win32 Communications functions and the new Delphi
'TThread' class. It is implemented using two threads: one for reading
from, and one for writing to a Comm Port. The Buffer received at
the port is copied and passed to the main thread, so there is no
reason to worry about syncronisation problems with the VCL.

CHANGES SINCE V1.1
==================
* Changed some variable names so they aren't so C-like (sorry)
* Fixed the bug where you had to wait for StartComm before sending data
* added Byte-size property

CHANGES SINCE V1.0
==================
* Added parity, stop-bit properties
* changed read-thread priority to 'Higher' instead of 'Highest'

KNOWN BUGS
==========
* Doesn't handle Comm-events very well.

USAGE
=====

To use the component once it is installed:
  1)  Attach an event handler to 'OnReceiveData'.
  2)  Call 'StartComm' to open the port.
  3)  Use the 'WriteCommData' method to write to the Comm port.
  4)  Call 'StopComm' to close the port.

CONTENTS
========
readme.txt   - this file
comm32.pas   - VC source file
comm32.dcr   - VC bitmap resource
project1.dpr
project1.res
unit1.pas
unit1.dfm    - demonstration program

LEGALITIES
==========

-----------
 Copyright
-----------
  Permission to use, copy and distribute this software and its documentation
  for any purpose and without fee is hereby granted, provided that it is not
  modified.

  THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

If you find it useful then I would appreciate any of the following:

*  Comments, Suggestions, Bug finds etc.
*  If you improve the component, please send me a copy of the changes.
*  Source code for any protocols such as Telnet and file-transfer
   (Kermit etc.)
*  A TAPI component

What I do not want is messages starting with "I am new to Delphi...". I
simply do not have time to support this product and not get paid for 
it. Write to me if you have found a problem, not if you have a problem
which can be answered by posting to the comp.lang.delphi.components
newsgroup.

David Wann
Stamina Software
7 Jun 96
E-mail:  davidwann@hunterlink.net.au

