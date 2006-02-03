"""module bots

"""
__revision__ = "$Id$"
__version__ = "1.0"

import re;
from string import replace;

def bot_compiled_regexp():
       return re.compile ("(([a-zA-Z]+)#([a-zA-Z0-9_]+))")
       #return re.compile ("(\[([a-zA-Z]+)#([a-zA-Z0-9]+)\])")

# Global
p_bot = bot_compiled_regexp()

def html_url_for(bot,id,name):
	bot_name = "%s.%s" % (__name__, bot)
	try:
		__import__(bot_name)
		cmd = "%s.html_url_for(\"%s\",\"%s\")" % (bot, id, name)
		return eval(cmd)
	except:
		return ""



def bots_html (html):
	global p_bot
	results = p_bot.findall( html)
	if results:
		for res in results:
			url = html_url_for(res[1],res[2],res[0])
			if len(url) > 0:
				html = replace (html, res[0], url)
	return html

