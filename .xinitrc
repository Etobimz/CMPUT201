#!/bin/bash

# user xinitrc file:
# $Id: Xinitrc.user 2225 2013-05-17 20:48:51Z johnb $

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

# source the global xinitrc
. /usr/local/rcfiles/Xinitrc.global
. $HOME/.xinitrc-options


# set the mouse acceleration and threshold
xset m 4 3

# turn on autorepeat
xset r on

# DON'T ADD ANYTHING BELOW THIS LINE
# window manager
start_window_manager ${my_window_manager}
