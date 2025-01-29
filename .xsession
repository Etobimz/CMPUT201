#!/bin/bash

# Standard xsession file:
# $Id: Xsession 2236 2013-05-25 00:11:25Z jmartin $

# Copyright (c) 2012 University of Alberta Department of Computing Science <helpdesk@cs.ualberta.ca>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


# Start an X Window session from connection through xdm
# set up source of login origination  - Bob Beck, Aug 1993

# first, we have to somehow get the user's environment set up 
# the way it should be.. In order to do this, we expect to 
# be able to use the appropriate .rc file from the user's home
# directory. For religious and techincal reasons we expect the 
# environment to be set in the .cshrc for C-shell-like shells
# in the .bashrc for gnu bash, and in the .profile for all others.

# Additionally, we expect the user to have a .xinitrc file
# normally used to start up X windows, accordingly, all this script
# does find out what shell you're supposed to be running, and 
# runs that shell doing A) a source of the .rc file to get your
# environment, and B) an exec of $HOME/xinitrc. Therefore, 
# FOR THIS SCRIPT TO WORK, $HOME/.[profile|login] must exist and 
# $HOME/.xinitrc must exist and be permitted executable. 
# if your files don't exist or aren't permtted correctly this
# script will run an xterm.

# xterm lives in different places on different distros
start-xterm() {
  case $DISTRO in
    slackware122)
      exec /usr/X11R6/bin/xterm
      ;;
    ubuntu1204)
      exec /usr/bin/X11/xterm
      ;;
    *)	# Hope for the best 
      exec /usr/X11R6/bin/xterm
      ;;
  esac
}

if [ -f $HOME/.bashrc -a -x $HOME/.xinitrc ]; then
  /bin/bash -c "(. $HOME/.bashrc; exec $HOME/.xinitrc)"
  /bin/bash -c "(. /usr/local/rcfiles/Bash_logout.global)"
else 
  start-xterm
fi
