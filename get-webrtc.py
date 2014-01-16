#!/usr/bin/python

"""
Copyright 2014 Alexey Kuzin <amkuzink@gmail.com>

This file is part of Melange.

Melange is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Melange is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Melange.  If not, see <http://www.gnu.org/licenses/>.
"""

import os, sys, argparse, pysvn

def default_checkout_path():
	source_dir_path = os.path.dirname(os.path.abspath(__file__))
	return os.path.join(source_dir_path,
		os.path.normcase('third_party/webrtc'))

def get_parser():
	#Initializes command-line argument parser
	parser = argparse.ArgumentParser(description='Checkout WebRTC source code')
	parser.add_argument('checkout_dir', action='store',
		nargs='?',
		default='',
		help='Destination path to checkout directory (default: "%s")' % default_checkout_path())

	return parser

def main():
	svn_client = pysvn.Client()

	parser = get_parser()
	args = parser.parse_args()
	if args.checkout_dir == '':
		args.checkout_dir = default_checkout_path()

	try:
		print('Checking out WebRTC...')
		#check out the current version of the webrtc project
		svn_client.checkout('http://webrtc.googlecode.com/svn/trunk/',
			args.checkout_dir)
		#get current revision
		revision = svn_client.info(args.checkout_dir).revision
		if revision.kind == pysvn.opt_revision_kind.number:
			print('Revision %d' % revision.number)
	except pysvn.ClientError as e:
		print(str(e))
	try:	
		#changing names of some source files due to problems with linkage
		path = './third_party/webrtc/webrtc/modules/audio_coding/codecs/ilbc'
		os.rename (path+'/encode.c', path+'/ilbc_encode.c')
		os.rename (path+'/decode.c', path+'/ilbc_decode.c')
	except os.error as e:
		print str(e)+". This may cause serious problems during linkage of webrtc."
	return 0

if __name__ == '__main__':
	sys.exit(main())
