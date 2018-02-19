Release notes for Maxwell 2D/3D version 10.0 (Nov. 2003)

Contents of this file
----------------------

I.   PC Operating Systems Supported

II.  Installation Notes
     A) Installing over a pre-released version of Maxwell EM v10
     B) Installing with existing Ansoft software
     C) FLEXlm
     D) TPC/IP Requirement
     E) Network Client Installation

III. Misc. Changes
     A) Licensing changes

IV.  Major New Features
     A) New features impacting all products
     B) New features in Maxwell 2D version 10.0
     C) New features in Maxwell 3D version 10.0

V.   WebUpdate

----------------------------------------------------------------------
I.   PC Operating Systems Supported
----------------------------------------------------------------------

Windows NT 4.0, Windows 2000 and Windows XP. This version may also run
on Windows 98/Me, but is not tested or officially supported any longer on
versions of Windows not based on NT. All executables are 32-bit on the PC.

----------------------------------------------------------------------
II.  Installation Notes
----------------------------------------------------------------------

A. Installing over a pre-released version of Maxwell EM v10

If you have previously installed a pre-release version of Maxwell EM
version 10 products, it is recommended that you un-install them before
installing this release. When you run the setup program on this CD,
it will enter "Maintenance" mode if a pre-release installation exists,
where you should choose the "Remove All" option. This will remove the
previous version of the software. You can then re-run the setup program
on this CD from the CD Autorun shell and proceed as a new installation.
You will not be presented with the "Maintenance" options if you have
not previously installed a pre-release version of Maxwell 10, or have
already un-installed the previous version.


B. Installing with existing Ansoft software

If you have other Ansoft software installed (including previous
versions of Maxwell), it is recommended that you install new software
in that same directory. Each new major version of Ansoft software
gets installed into a unique sub-directory within the installation
directory specified. This allows different Ansoft software, as well
as newer versions of the same software to co-exist independently of
one another. This also permits the communication between certain
products, such as Ansoft Optimetrics and those products it supports,
to perform as designed.


C. FLEXlm

FLEXlm is the only supported licensing mechanism. The FLEXlm
license server is presented as a separate item in the installation.
We have upgraded to a more recent version of FLEXlm. FLEXlm is
presented as a separate item so that customers can more easily
install the license server on a different machine from the
machine(s) on which they install the software.

NOTE: If you are evaluating the software you will receive
time-stamped, uncounted licenses locked to a single machine.
You do not need to install the FLEXlm server software to run
using uncounted licenses.


D.  TPC/IP Requirement

FLEXlm requires that the TCP/IP network protocol is installed
on your computer, even if your computer is not attached to a network.

TCP/IP and Windows NT 4.0

To see if you have TCP/IP installed under Windows NT 4.0:

1) Choose "Start - Settings - Control Panel"
2) Double click the "Network" applet in the Windows Control
Panel.
3) On the "Protocols" tab, make sure that "TCP/IP Protocol"
is listed under "Network Protocols".

To install TCP/IP if it is not already installed under
Windows NT 4.0 (you must be administrator):

1) On the "Protocols" tab, Click on "Add".
2) In the "Network Protocols" list, click on "TCP/IP Protocol",
then choose "OK".
3) Click "Yes" to use DHCP (Dynamic Host Configuration Protocol)
in order to configure TCP/IP automatically, or click "No" to
configure TCP/IP manually.
4) When prompted, enter the full path to the Windows NT
distribution files and click "Continue". All necessary files
will be copied to your hard disk.

TCP/IP and Windows 2000

To see if you have TCP/IP installed under Windows 2000:

1) Choose "Start - Settings - Control Panel"
2) Double click the "Network and Dial Up Connections" applet
in the Windows Control Panel.
3) In the "Network and Dial Up Connections" window, double
click "Local Area Connection".
4) In the "Local Area Connection Status" window, click on the
"General" tab then choose "Properties". Make sure that
"Internet Protocol (TCP/IP)" is listed.

To install TCP/IP if it is not already installed under
Windows 2000 (you must be administrator):

1) On the "General" tab, click "Install..."
2) Click "Protocol", then click "Add".
3) In the "Select Network Protocol" dialog, click
"Internet Protocol (TCP/IP), then click "OK".
4) Verify that the "Internet Protocol (TCP/IP" check box
is selected, and click "OK".

NOTE: For more information on installing or configuring
TCP/IP, choose "Help" from the Windows "Start" menu, then
enter "TCP/IP" on the Index Search tab. 


E. Network Client Installation

Although not recommended, you may want to run Maxwell EM Products on a
computer from a network server without installing the software locally.
In order to do this, you will need to run the Network Client
installation. This setup program is not available as a menu item from
the CD Autorun shell, it is located in the NetClient directory on this CD.
>From the Windows Start menu, choose "Run" and click the "Browse" button
and locate setup.exe in the NetClient directory. The Network Client
installation only installs appropriate runtime DLL's required to be
present on a computer in order to run Maxwell EM Products, and creates
a Start Menu link to maxwell.exe residing on the server. It does not
install any of the other Ansoft executables. IF YOU ARE INSTALLING
THE SOFTWARE LOCALLY, YOU DO NOT NEED TO RUN THE NETWORK CLIENT
INSTALLATION EVEN IF YOUR LICENSE SERVER IS ANOTHER COMPUTER ON
THE NETWORK.

----------------------------------------------------------------------
III. Misc. Changes
----------------------------------------------------------------------

A. Licensing changes

The version numbers of the licensed features used in this software
has been increased since the previous release. If you already have
licenses for Maxwell 9, you will need to request new licenses.

Product CD's no longer contain the FLEXlm for Ansoft installation.
The FLEXlm for Ansoft installation is now on a separate CD, which
covers all supported platforms. The latest version of FLEXlm for
Ansoft uses the FLEXlm 8.4a license server. Please install this
version.

----------------------------------------------------------------------
IV.  Major New Features
----------------------------------------------------------------------

A. New features impacting all products

Support has been added for new USB dongle (FLEXID-9). 

The PC installation now supports silent installation. This allows you
to record your actions and choices while installing the software and
then use the recorded script to automate the installation on identical
machines. This is very useful for universities and large corporations
with multiple seats.


B. Major new features in Maxwell 2D version 10.0

Adaptive time stepping has been added for 2D transient projects.

A new more robust meshmaker (meshv7) has been added. The new meshmaker
is used for initial meshes and adaptive refinement. The new meshmaker is
non-graphical. The older program (meshv6) is still used for manual mesh
generation.

Controls have been added to the solution setup panel for nonlinear
magnetostatic projects (called Advanced Nonlinear Options) to allow you
to solve a project in one set of excitations and material surroundings
and compute and save the demagnetized operating point for magnets and
the permeability for nonlinear materials then to use these values for
a second simulation using different conditions.

In the postprocessor for transient projects you can now compute and
plot the froce distribution and calculate core loss. There have also
been several bugs fixed in mu and H calculation/plotting.

Support is added to do co-simulation between Simplorer and Maxwell 2D
transient.


C. Major new features in Maxwell 3D version 10.0

The 3D EM transient solver now supports rotational motion and 1-
dimensional translational motion.

A 3D transient thermal solver has been added (with adaptive time 
stepping). This allows you to do transient thermal simulations either
as standalone analysis or one-way coupled with Magnetostatic or Eddy
Current solutions (with loss calculations from those solutions used
as heat sources for the thermal analysis. You can setup a series of
steady-state EM solutions as the source condition for the transient
thermal analysis.

A 3D static stress solver has been added. This allows you to do
standalone stress simulation, but also allows stress driven by forces
from almost any of the other types of 3D field analysis. 

STEP/IGES translation has changed. Success rates should be considerably
higher.

The 3D modeler is now based on ACIS 8.0 libraries.

Controls have been added to the solution setup panel for nonlinear
magnetostatic projects (called Advanced Nonlinear Options) to allow you
to solve a project in one set of excitations and material surroundings
and compute and save the demagnetized operating point for magnets and
the permeability for nonlinear materials then to use these values for
a second simulation using different conditions.

In the postprocessor, you can now do core loss calculations in EM
transient. Transient thermal and stress postprocessing have been 
added along with transient animations of temperature for thermal
transient and displacement for stress.

----------------------------------------------------------------------
V.   WebUpdate
----------------------------------------------------------------------

This CD contains WebUpdate for Ansoft products. WebUpdate is an
application which allows you to automatically check for product
updates from the Ansoft support website. If an update is available
for a particular product, it can be downloaded and automatically
installed through the WebUpdate application.
