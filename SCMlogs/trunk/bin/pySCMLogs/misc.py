#!/usr/bin/python
#
# Usage:  svn_sendlogs.py -f logfile { -u user } { -p filterfile or none } {-html}
#

from time import *
import sys;
import re;
import os;
from string import split, replace, rstrip, strip;

# Configuration
#from pySCMLogs.configdev import *

###################################
# Declaration
###################################

