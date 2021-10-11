" Tab and Indent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set smarttab
"set expandtab  " Use the space to instead of tab
set autoindent  " Copy indent from current line when starting a new line
set smartindent
set cindent

" Seach and Match
set hlsearch  " Highlight the search result
set incsearch  " Real-time search
set ignorecase
set smartcase
set showmatch  " When a bracket is inserted, briefly jump to the matching one

set nocompatible  " Use the vim's keyboard setting, not vi

if filereadable(expand("~/.vim/vimrc.vundle"))
  source ~/.vim/vimrc.vundle
endif

set nu  " Set the line number
syntax on  " Syntax highlighting
"set autochdir  " Set the current dir as thr work dir
filetype on  " File type detection
filetype plugin on  " Loading the plugin files for specific file types
filetype indent on  " Loading the indent file for specific file types with

" mouse
set mouse=a
set mousehide

set cursorline "highlit curren line
