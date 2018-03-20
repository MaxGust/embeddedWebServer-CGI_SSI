# embeddedWebServer-CGI_SSI [![Build Status](https://travis-ci.org/vppillai/embeddedWebServer-CGI_SSI.svg?branch=master)](https://travis-ci.org/vppillai/embeddedWebServer-CGI_SSI)
frugal embedded webserver implimentation with CGI and SSI

Build and tested in travis for Clang and GCC with -C99 using the following build options

` -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -pedantic -std=c99 -Werror `

1.	Design objectives
This web server design needs to be:
-	Light weight and small embedded system friendly
-	Portable across RTOS and bare-metal systems
-	Portable across networking mechanisms
-	Portable across filesystems. 
2.	Functionality
This web server design needs to include the following capabilities
-	static web pages
-	dynamic pages including:
 - Support for Server Side Includes (SSI)
 - Support for CGI 
