# Source system global definitions
if [ -f /etc/bashrc ]; then
  . /etc/bashrc
fi
alias git_save_passwd='git config credential.helper store'
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'
alias ll='ls -lh'
