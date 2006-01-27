#!/usr/bin/python

import re
from string import split, replace, rstrip, strip, atoi ;
import bots;

# Global
p_bot = bots.bot_compiled_regexp()

def processed_formatted_html (html):
	global p_bot
	results = p_bot.findall( html)
	if results:
		for res in results:
			url = bots.html_url_for(res[1],res[2],res[0])
			if len(url) > 0:
				html = replace (html, res[0], url)
	return html

def text_to_formated_html_escape (txt):
	# escape the  '<' and '>' to htmlentities
	result = "%s"  % (txt)
	result = replace (result, "<","&lt;")
	result = replace (result, ">","&gt;")
	result = replace (result, "\n", "<br/>\n")
	#result = replace (result, "\ ", "&nbsp;")
	result = replace (result, "    ", "&nbsp;&nbsp;&nbsp;&nbsp;")
	result = replace (result, "\t", "&nbsp;&nbsp;&nbsp;&nbsp;")
	return result

