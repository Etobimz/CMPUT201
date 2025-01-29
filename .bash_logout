# User bash_logout file:
# $Id: Bash_logout.user 2983 2016-09-08 17:39:23Z johnb $
#
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
#

# print nice hand holding message
# we do this here because we want the global logout to be silent
echo "Cleaning up temporary files..."


# source the global logout script
source /usr/local/rcfiles/Bash_logout.global


# give quota check for students who won't check it otherwise
# Note to user: you are responsible for keeping yourself below quota!
echo ""
echo "`hostname`: `whoami` logged out at `date`"
echo ""
# Let users know how much share space is left
if [ x$CCID = "xyes" ]; then
  usage=`fs lq $HOME|grep -v Quota|awk '{print $3}'`
  share_size=`fs lq $HOME|grep -v Quota|awk '{print $2}'`
  echo $usage $share_size | awk '{printf "Your AFS quota is:\nUsed:%13d MB\nAvailable:%8d MB\n",$1/1024,$2/1024}'
else
  if [[ ${DISTRO} ]]; then
    case ${DISTRO} in
      slackware122)
        DF=`df -P $HOME | grep "$HOME$"`;
      ;;
      ubuntu1204)
        DF=`df $HOME | grep "$HOME$"`;
      ;;
      ubuntu1404)
        DF=`df $HOME | grep "$HOME$"`;
      ;;
      rhel59)
        DF=`df -P $HOME | grep "$HOME$"`;
      ;;
      undefined)
        DF=`df $HOME | grep "$HOME$"`;
      ;;
      *)
        DF=`df $HOME | grep "$HOME$"`;
      ;;
    esac
  else
    DF=`df $HOME| grep "$HOME$"`;
  fi
  echo $DF | awk '{printf "Your Home directory Share space:\nUsed:%13s MB\nAvailable:%8s MB\n",$3/1024,$2/1024}'
fi

echo ""
echo "Goodbye\!"

exit 0
