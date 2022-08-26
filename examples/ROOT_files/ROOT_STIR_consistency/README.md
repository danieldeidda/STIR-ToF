# TOF consistency checks for STIR
## Authors: Elise Emond & Robert Twyman

Copyright (C) 2022, University College London
  This file is part of STIR.
SPDX-License-Identifier: Apache-2.0
See STIR/LICENSE.txt for details

These files were included to :
* Test non-TOF ROOT and STIR consistency, particularly the rotation.
* Test the TOF STIR implementation was correct (NOT YET IMPLEMENTED).

Directories
-----

- `SourceFiles/`: Contains 8 `generate_image` parameter files and GATE macro files for the emission source positions. One pair of files for each test.
- `Gate_macros/`: Contains the GATE macro files for generating the data.
- `DebugScripts`: Contains scripts for better understanding the tests.


FILES
----

- `README.md`: This file.
- `root_header_test_template.hroot`: Template file for generating root header files for each of the test list mode data files that are generated by GATE.
- `run_pretest_script.sh`: The main script for generating the data (requires GATE). This script runs GATE simulations for each test emission and generates the root header files for them.


______

Methodology
----
 1. Generate the ROOT data. 
     1. Run `./run_pretest_script.sh` in the terminal to generate the ROOT files (requires Gate) for different point sources, or
     2. Download the ROOT data and proceed without Gate simulation.
     
 2. Run the STIR test: `src/recon_test/test_view_offset_root`.
    This test should tell you whether it failed or not by testing if the LOR passes by, 
    or close to, the original point source position.
 3. Run the python scripts in `DebugScripts` to better understand erros and to give a more in-depth analysis.


_____

SOURCE POSITION CONFIGURATION
-----
In GATE coordinates (`mm`), the point sources positions are as follows:

| ID | x | y | z | comment |
| :---: | :---: | :----: | :---: | :---: |
| **1** | 0 | 0 | 0 | center scanner |
| **2** | 190 | 0 | 0 | +x |
| **3** | 0 | 190 | 0 | +y  |
| **4** | 95 | 95 | 0 | +x +y |
| **5** | 0 | 0 | 70 | +z | 
| **6** | 190 | 0 | 70 | +x +z |
| **7** | 0 | 190 | 70 |  +y +z |
| **8** | 95 | 95 | 70 |  +x +y +z |

_Note_: The activity of testIDs 5-8 are 10x that of 1-4 because of the large z-shift.

GATE defines its origin at the center of the scanner.
STIR defines its origin in the center of the first ring of the scanner.
Hence, a translation is needed to convert between from GATE's origin to STIR's.
This is given by:

```
stir_z = (L-d)/2 + gate_z
``` 

where `L` is the scanner z-length (`157.16 mm`) and `d = 6.54mm` is the distance between rings .
For the data currently used in this test, `(L-d)/2 = 75.31mm`.
There are no translations in x or y. 
