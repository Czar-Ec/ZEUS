# Convert Font Awesome, Fork Awesome, Google Material Design, Kenney Game and Ionicons
# icon font parameters to C89 and C++11 compatible formats.
#
#------------------------------------------------------------------------------
# 1 - Source material
#
#   1.1 - Font Awesome
#		1.1.1 - version 4
#			https://raw.githubusercontent.com/FortAwesome/Font-Awesome/fa-4/src/icons.yml
#			https://github.com/FortAwesome/Font-Awesome/blob/fa-4/fonts/fontawesome-webfont.ttf
#		1.1.2 - version 5
#			https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/advanced-options/metadata/icons.yml
#			https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-brands-400.ttf
#			https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-regular-400.ttf
#			https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-solid-900.ttf
#	1.2 - Fork Awesome
# 			https://raw.githubusercontent.com/ForkAwesome/Fork-Awesome/master/src/icons/icons.yml
# 			https://github.com/ForkAwesome/Fork-Awesome/blob/master/fonts/forkawesome-webfont.ttf
#   1.3 - Google Material Design
# 			https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints
#			https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf
#   1.4 - Kenney Game icons
# 			https://raw.githubusercontent.com/nicodinh/kenney-icon-font/master/css/kenney-icons.css
#			https://github.com/nicodinh/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf
#   1.4 - Ionicons
# 			https://raw.githubusercontent.com/ionic-team/ionicons/master/css/ionicons.css
#			https://github.com/ionic-team/ionicons/blob/master/fonts/ionicons.ttf
#
#------------------------------------------------------------------------------
# 2 - Data samples
#
#   2.1 - Font Awesome
#           - input:            music:
#                                 changes:
#                                   - '1'
#                                   - 5.0.0
#                                 label: Music
#                                 search:
#                                   terms:
#                                     - note
#                                     - sound
#                                 styles:
#                                   - solid
#                                 unicode: f001
#           - output C++11:     #define ICON_FA_MUSIC u8"\uf001"
#           - output C89:       #define ICON_FA_MUSIC "\xEF\x80\x81"
#
#   2.2 - Fork Awesome
#           - input: 			see Font Awesome
#           - output C++11:     #define ICON_FK_MUSIC u8"\uf001"
#           - output C89:       #define ICON_FK_MUSIC "\xEF\x80\x81"
#
#   2.3 - Google Material Design
#           - input:            3d_rotation e84d
#           - output C++11:     #define ICON_MD_3D_ROTATION u8"\ue84d"
#           - output C89:       #define ICON_MD_3D_ROTATION "\xEE\xA1\x8D"
#
#   2.4 - Kenney Game
#           - input:            .ki-home:before{ content: "\e900"; }
#           - output C++11:     #define ICON_KI_HOME u8"\ue900"
#           - output C89:       #define ICON_KI_HOME "\xEE\xA4\x80"
#
#   2.4 - Ionicons
#           - input:            .ion-alert:before { content: "\f101"; }
#           - output C++11:     #define ICON_II_ALERT u8"\uf101"
#           - output C89:       #define ICON_II_ALERT "\xEF\x84\x81"
#
#   2.5 - All fonts
#           - computed min and max unicode fonts ICON_MIN and ICON_MAX
#           - output C89, C++11:	#define ICON_MIN_FA 0xf000
#                               	#define ICON_MAX_FA 0xf295
#
#------------------------------------------------------------------------------
# 3 - Script dependencies
#
#   3.1 - Fonts source material online
#   3.2 - Python 2.7 - https://www.python.org/download/releases/2.7/
#   3.3 - Requests - http://docs.python-requests.org/
#   3.4 - PyYAML - http://pyyaml.org/
#
#------------------------------------------------------------------------------
# 4 - References
#
# 	GitHub repository: https://github.com/juliettef/IconFontCppHeaders/
#
#------------------------------------------------------------------------------


import requests
import yaml


# Fonts

class Font:
	font_name = '[ ERROR - missing font name ]'
	font_abbr = '[ ERROR - missing font abbreviation ]'
	font_url_data = '[ ERROR - missing font data url ]'
	font_url_ttf = '[ ERROR - missing ttf file url ]'
	font_file_name_ttf = '[ ERROR - missing ttf file name ]'

	@classmethod
	def get_icons( cls, input ):
		# intermediate representation of the fonts data, identify the min and max
		print( '[ ERROR - missing implementation of class method get_icons for {!s} ]'.format( cls.font_name ))
		icons_data = {}
		icons_data.update({ 'font_min' : '[ ERROR - missing font min ]',
							'font_max' : '[ ERROR - missing font max ]',
							'icons' : '[ ERROR - missing list of pairs [ font icon name, code ]]' })
		return icons_data

	@classmethod
	def download( cls ):
		input_raw = ''
		try :
			response = requests.get( cls.font_url_data, timeout = 2 )
			if response.status_code == 200:
				input_raw = response.content
				print( 'Downloaded - ' + cls.font_name )
		except Exception as e :
			print( '[ ERROR - {!s}: {!s} ]'.format( cls.font_name, e ))
		return input_raw

	@classmethod
	def get_intermediate_representation( cls ):
		font_ir = {}
		input_raw = cls.download()
		if input_raw:
			icons_data = cls.get_icons( input_raw )
			font_ir.update( icons_data )
			font_ir.update({ 'font_url_ttf' : cls.font_url_ttf,
							 'font_url_data' : cls.font_url_data,
							 'font_file_name_ttf' : cls.font_file_name_ttf,
							 'font_name' : cls.font_name,
							 'font_abbr' : cls.font_abbr })
			print( 'Generated intermediate data - ' + cls.font_name )
		return font_ir


class FontFA4( Font ):	# legacy Font Awesome version 4
	font_name = 'Font Awesome 4'
	font_abbr = 'FA'
	font_url_data = 'https://raw.githubusercontent.com/FortAwesome/Font-Awesome/fa-4/src/icons.yml'
	font_url_ttf = 'https://github.com/FortAwesome/Font-Awesome/blob/fa-4/fonts/fontawesome-webfont.ttf'
	font_file_name_ttf = [[ font_abbr, font_url_ttf[ font_url_ttf.rfind('/')+1: ]]]

	@classmethod
	def get_icons( self, input ):
		icons_data = { }
		data = yaml.safe_load(input)
		font_min = 'ffff'
		font_max = '0'
		icons = []
		for item in data[ 'icons' ]:
			if item[ 'unicode' ] < font_min:
				font_min = item[ 'unicode' ]
			if item[ 'unicode' ] >= font_max:
				font_max = item[ 'unicode' ]
			icons.append([ item[ 'id' ], item[ 'unicode' ]])
		icons_data.update({ 'font_min' : font_min,
						'font_max' : font_max,
						'icons' : icons })
		return icons_data


class FontFK( FontFA4 ):	# Fork Awesome, based on Font Awesome 4
	font_name = 'Fork Awesome'
	font_abbr = 'FK'
	font_url_data = 'https://raw.githubusercontent.com/ForkAwesome/Fork-Awesome/master/src/icons/icons.yml'
	font_url_ttf = 'https://github.com/ForkAwesome/Fork-Awesome/blob/master/fonts/forkawesome-webfont.ttf'


class FontFA5( Font ):	# Font Awesome version 5. Solid and Regular styles (Regular is a subset of Solid).
	font_name = 'Font Awesome 5'
	font_abbr = 'FA'
	font_url_data = 'https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/advanced-options/metadata/icons.yml'
	font_url_ttf = 'https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-solid-900.ttf, ' +\
		'https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-regular-400.ttf, '
	font_file_name_ttf = [[ 'FAS', 'fa-solid-900.ttf' ], [ 'FAR', 'fa-regular-400.ttf' ]]
	font_fa_style = [ 'solid', 'regular' ]

	@classmethod
	def get_icons( self, input ):
		icons_data = { }
		data = yaml.safe_load(input)
		if data:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for key in data:
				item = data[ key ]
				for style in item[ 'styles' ]:
					if style in self.font_fa_style:
						if [ key, item[ 'unicode' ]] not in icons:
							if item[ 'unicode' ] < font_min:
								font_min = item[ 'unicode' ]
							if item[ 'unicode' ] >= font_max:
								font_max = item[ 'unicode' ]
							icons.append([ key, item[ 'unicode' ] ])
			icons_data.update({ 'font_min':font_min, 'font_max':font_max, 'icons':icons })
		return icons_data


class FontFA5Brands( FontFA5 ):	# Font Awesome version 5, Brand styles.
	font_name = 'Font Awesome 5 Brands'
	font_abbr = 'FAB'
	font_url_ttf = 'https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-brands-400.ttf'
	font_file_name_ttf = [[ font_abbr, font_url_ttf[ font_url_ttf.rfind('/') + 1: ]]]
	font_fa_style = [ 'brands' ]

	@classmethod
	def get_icons( self, input ):
		icons_data = { }
		data = yaml.safe_load(input)
		if data:
			font_min = 'ffff'
			font_max = '0'
			icons = [ ]
			for key in data:
				item = data[ key ]
				for style in item[ 'styles' ]:
					if style in self.font_fa_style:
						if item[ 'unicode' ] < font_min:
							font_min = item[ 'unicode' ]
						if item[ 'unicode' ] >= font_max:
							font_max = item[ 'unicode' ]
						icons.append([ key, item[ 'unicode' ]])
			icons_data.update({ 'font_min':font_min, 'font_max':font_max, 'icons':icons })
		return icons_data


class FontMD( Font ):	# Material Design
	font_name = 'Material Design'
	font_abbr = 'MD'
	font_url_data = 'https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints'
	font_url_ttf = 'https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf'
	font_file_name_ttf = [[ font_abbr, font_url_ttf[ font_url_ttf.rfind('/')+1: ]]]

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		lines = str.split( input, '\n' )
		if lines:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for line in lines :
				words = str.split(line)
				if words and len( words ) >= 2:
					if words[ 1 ] < font_min:
						font_min = words[ 1 ]
					if words[ 1 ] >= font_max:
						font_max = words[ 1 ]
					icons.append( words )
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons })
		return icons_data


class FontKI( Font ):	# Kenney Game icons
	font_name = 'Kenney'
	font_abbr = 'KI'
	font_url_data = 'https://raw.githubusercontent.com/nicodinh/kenney-icon-font/master/css/kenney-icons.css'
	font_url_ttf = 'https://github.com/nicodinh/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf'
	font_file_name_ttf = [[ font_abbr, font_url_ttf[ font_url_ttf.rfind('/')+1: ]]]

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		lines = str.split( input, '\n' )
		if lines:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for line in lines :
				if '.ki-' in line:
					words = str.split(line)
					if words and '.ki-' in words[ 0 ]:
						font_id = words[ 0 ].partition( '.ki-' )[2].partition( ':before' )[0]
						font_code = words[ 2 ].partition( '"\\' )[2].partition( '";' )[0]
						if font_code < font_min:
							font_min = font_code
						if font_code >= font_max:
							font_max = font_code
						icons.append([ font_id, font_code ])
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons  })
		return icons_data


class FontII( Font ):	# Ionicons
	font_name = 'Ionicons'
	font_abbr = 'II'
	font_url_data = 'https://raw.githubusercontent.com/ionic-team/ionicons/master/css/ionicons.css'
	font_url_ttf = 'https://github.com/ionic-team/ionicons/blob/master/fonts/ionicons.ttf'
	font_file_name_ttf = [[ font_abbr, font_url_ttf[ font_url_ttf.rfind('/') + 1: ]]]

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		lines = str.split( input, '\n' )
		if lines:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for line in lines :
				if ( '.ion-' and 'content:' ) in line:
					words = str.split(line)
					if words and '.ion-' in words[ 0 ]:
						font_id = words[ 0 ].partition( '.ion-' )[2].partition( ':before' )[0]
						font_code = words[ 3 ].partition( '"\\' )[2].partition( '";' )[0]
						if font_code < font_min:
							font_min = font_code
						if font_code >= font_max:
							font_max = font_code
						icons.append([ font_id, font_code ])
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons  })
		return icons_data


# Languages


class Language:
	language_name = '[ ERROR - missing language name ]'
	file_name = '[ ERROR - missing file name ]'
	intermediate = {}

	def __init__( self, intermediate ):
		self.intermediate = intermediate

	@classmethod
	def prelude( cls ):
		print('[ ERROR - missing implementation of class method prelude for {!s} ]'.format( cls.language_name ))
		result = '[ ERROR - missing prelude ]'
		return result

	@classmethod
	def lines_minmax( cls ):
		print('[ ERROR - missing implementation of class method lines_minmax for {!s} ]'.format( cls.language_name ))
		result = '[ ERROR - missing min and max ]'
		return result

	@classmethod
	def line_icon( cls, icon ):
		print('[ ERROR - missing implementation of class method line_icon for {!s} ]'.format( cls.language_name ))
		result = '[ ERROR - missing icon line ]'
		return result

	@classmethod
	def convert( cls ):
		result = cls.prelude() + cls.lines_minmax()
		for icon in cls.intermediate.get( 'icons' ):
			line_icon = cls.line_icon( icon )
			result += line_icon
		print ( 'Converted - {!s} for {!s}' ).format( cls.intermediate.get( 'font_name' ), cls.language_name )
		return result

	@classmethod
	def save_to_file( cls ):
		filename = cls.file_name.format( name = str(cls.intermediate.get( 'font_name' )).replace( ' ', '' ))
		converted = cls.convert()
		with open( filename, 'w' ) as f:
			f.write( converted )
		print( 'Saved - {!s}' ).format( filename )


class LanguageC89( Language ):
	language_name = 'C89'
	file_name = 'Icons{name}_c.h'

	@classmethod
	def prelude( cls ):
		tmpl_prelude = '// Generated by https://github.com/juliettef/IconFontCppHeaders script GenerateIconFontCppHeaders.py for language {lang}\n' + \
			'// from {url_data}\n' + \
			'// for use with {url_ttf}\n' + \
			'#pragma once\n\n'
		result = tmpl_prelude.format(lang = cls.language_name,
									 url_data = cls.intermediate.get( 'font_url_data' ),
									 url_ttf = cls.intermediate.get( 'font_url_ttf' ))
		tmpl_prelude_define_file_name = '#define FONT_ICON_FILE_NAME_{font_abbr} "{file_name_ttf}"\n'
		file_names_ttf = cls.intermediate.get( 'font_file_name_ttf' )
		for file_name_ttf in file_names_ttf:
			result += tmpl_prelude_define_file_name.format( font_abbr = file_name_ttf[ 0 ], file_name_ttf = file_name_ttf[ 1 ])
		return result + '\n'

	@classmethod
	def lines_minmax( cls ):
		tmpl_line_minmax = '#define ICON_{minmax}_{abbr} 0x{val}\n'
		result = tmpl_line_minmax.format(minmax = 'MIN',
										 abbr = cls.intermediate.get( 'font_abbr' ),
										 val = cls.intermediate.get( 'font_min' )) + \
				 tmpl_line_minmax.format(minmax = 'MAX',
										 abbr = cls.intermediate.get( 'font_abbr' ),
										 val = cls.intermediate.get( 'font_max' ))
		return result

	@classmethod
	def line_icon( cls, icon ):
		tmpl_line_icon = '#define ICON_{abbr}_{icon} "{code}"\n'
		icon_name = str.upper( icon[ 0 ]).replace( '-', '_' )
		code_base = ''.join([ '{0:x}'.format( ord( x )) for x in unichr( int( icon[ 1 ], 16 )).encode( 'utf-8' )]).upper()
		icon_code = '\\x' + code_base[ :2 ] + '\\x' + code_base[ 2:4 ] + '\\x' + code_base[ 4: ]
		result = tmpl_line_icon.format( abbr = cls.intermediate.get( 'font_abbr' ),
										icon = icon_name,
										code = icon_code )
		return result


class LanguageCpp11( LanguageC89 ):
	language_name = 'C++11'
	file_name = 'Icons{name}.h'

	@classmethod
	def line_icon( cls, icon ):
		tmpl_line_icon = '#define ICON_{abbr}_{icon} u8"\u{code}"\n'
		icon_name = str.upper( icon[ 0 ]).replace( '-', '_' )
		icon_code = icon[ 1 ]
		result = tmpl_line_icon.format( abbr = cls.intermediate.get( 'font_abbr' ),
										icon = icon_name,
										code = icon_code)
		return result


# Main
fonts = [ FontFA4, FontFA5, FontFA5Brands, FontFK, FontMD, FontKI, FontII ]
languages = [ LanguageC89, LanguageCpp11 ]

intermediates = []
for font in fonts:
	intermediates.append( font.get_intermediate_representation())
for interm in intermediates:
	Language.intermediate = interm
	for lang in languages:
		lang.save_to_file()
