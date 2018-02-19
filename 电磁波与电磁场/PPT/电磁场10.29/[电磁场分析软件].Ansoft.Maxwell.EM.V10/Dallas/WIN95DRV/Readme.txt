INSTALLING THE VSAUTHD.VXD DRIVER FOR WINDOWS 95.

The Vsauthd.vxd device driver is required for communication to the 
the DS1410D, the DS1410E, and Buttons in Windows 95.  The device driver is used for native 32-bit Windows 95 applications.

To install the Vsauthd.vxd device driver please perform the following steps:  


1.	Copy the file \Win95\Driver\Vsauthd.vxd to the \Windows\System directory.

2.	Place the DS1410E and Button(s) on the parallel port.

3.	Run Lmtools -> hostid, or lmutil lmhostid -flexid


You can also use the Vsauthd.vxd driver with the Setup.exe program in the winntdrv
directory, it will autodetect the operating system and install the proper driver