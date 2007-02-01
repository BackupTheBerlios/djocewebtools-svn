#!/usr/bin/python
import smtplib
import string
import os
import sys
import re
from time import *

# Configuration
from pyMyReporting.config import *

email_mode_new = "new"
email_mode_report = "report"
email_mode_refresh = "refresh"
email_mode_remind = "remind"

def sendMailToFromSubjectOfOn (z_to, z_from_name, z_from, z_mail, z_server) :
	fromaddr = 'From: "' + z_from_name + '" <' + z_from + '>'
	toaddrs = 'To: <' + z_to + '>'
	msg = z_mail
	server = smtplib.SMTP(z_server)
	server.sendmail(fromaddr, toaddrs, msg)
	server.quit()

def ActiveUsers (z_reporters_file):
	# Get the reporters file content as a list of lines
	myfile = open (z_reporters_file, 'r');
	reporters_lines = re.split ("\n", myfile.read())
	myfile.close ();

	regexp = "^([a-zA-Z]+)\s*,\s*(.*)\s*,\s*(.*)\s*,\s*(.*)\s*,\s*(.*)\s*$"
	p = re.compile (regexp);

	active_reporters =[]
	for reporter in reporters_lines:
		result = p.search (reporter,0)
		if result:
			#print "-"*70;
			#print "Login=%s" % (result.group (1))
			#print "Name=%s" % (result.group (2))
			#print "Team=%s" % (result.group (3))
			#print "Web=%s" % (result.group (4))
			#print "Active=%s" % (result.group (5))
			reporter_status = result.group (5)
			#print "STATUS = %s SIZE= %i GOOD= %i" % (reporter_status[0:6] ,len(reporter_status), len ("Active"))
			if (len (reporter_status) >= len ("Active")) and reporter_status[0:6] == "Active" :
				active_reporters.append ( result.group(1) )

	#return only active reporter from this file
	return active_reporters

def weekMailContent (z_include_report, z_good_reporters, z_bad_reporters, z_week_number_string, z_week_url, z_week_filename, z_to_address, z_superreporter) :

	z_today = strftime ("%A %d %B %Y (%H:%M:%S)", localtime(time()))
	good_text = "<STRONG>Good reporters : </STRONG> "
	for good_reporter in z_good_reporters:
		good_text = good_text + good_reporter + ", "
	bad_text = "<STRONG>Late reporters : </STRONG> "
	for bad_reporter in z_bad_reporters:
		bad_text = bad_text + bad_reporter + ", "

	    # Message Header
	message_header = ""
	message_header = message_header +  "X-Mailer: PyJoceMailer\n"
	message_header = message_header +  "Reply-To: <%s>\n" % (z_superreporter)
	message_header = message_header +  'From: "' + sender_name + '" <' + sender_email + '>\n'
	message_header = message_header +  "To: <%s>\n" % (z_to_address)
	message_header = message_header +  "Subject: REPORT %s \n" % (z_week_number_string)
	message_header = message_header +  "Organization: %s \n" % (organization_name)

	message_header = message_header +  "MIME-Version: 1.0\n"
	message_header = message_header +  "Content-Type: text/html;\n\n"
	message_header = message_header + '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">'

	    # Message Content
	message_to_add = ""
	message_to_add = message_to_add +  "Reports for week %s is ready <BR><UL><A STYLE='background-color: #FFFF00;' HREF='%s'>%s</A></UL><BR>\n" % (z_week_number_string, z_week_url, z_week_url) 
	message_to_add = message_to_add +  "<STRONG>Date : </STRONG>%s<BR>\n" % (z_today)
	message_to_add = message_to_add +  good_text + "<BR>\n"
	message_to_add = message_to_add +  bad_text + "<BR>\n"
	message_to_add = message_to_add +  "<HR>\n"
	message_to_add = message_to_add +  "URL : <A HREF=\"%s\">MyReporting web page</A> <BR>\n" % (reporting_web_path)
	message_to_add = message_to_add +  "For any request <A HREF=\"mailto:%s\">email me</A> <BR>\n" % (z_superreporter)
	message_to_add = message_to_add +  "<HR>\n\n"

	if z_include_report:
			# Building email source
		myweekfile = open (z_week_filename, 'r');
		message_body = myweekfile.read();
		myweekfile.close ();

		p = re.compile ("\.\.\/\.\.\/\.\.\/")
		zto = reporting_web_path
		message_body = p.sub (zto, message_body, 1)

		p = re.compile ("\<[Bb][Oo][Dd][Yy]\>")
		zto = "<BODY>\n%s" % (message_to_add)
		message_body = p.sub (zto, message_body, 1)
	else :
		message_body = "<HTML><BODY>%s</BODY></HTML>" % (message_to_add);
	message = message_header + message_body
	return message

def badReporterMailContent (z_bad_reporter, z_week_number_string, z_week_url, z_to_address, z_superreporter) :

	z_today = strftime ("%A %d %B %Y (%H:%M:%S)", localtime(time()))
	message = ""

	message = message +  "X-Mailer: PyJoceMailer\n"
	message = message +  "MIME-Version: 1.0\n"
	message = message +  "To: %s\n" % (z_to_address)
	message = message +  "Subject: [REPORTING] %s Your Report %s is missing \n" % (z_bad_reporter, z_week_number_string)
	message = message +  "Reply-To: %s\n" % (z_superreporter)
	message = message +  "Content-Type: text/html\n"
	message = message +  "\n\n"
	message = message +  "%s , you forgot to add your report for week %s<BR><STRONG STYLE='color:red;'>Please go and add your report</STRONG> from <UL><A STYLE='background-color: #FFFF00;' HREF='%s?rub=post&username=%s&week=%s'>%s</A></UL><BR>\n" % (z_bad_reporter, z_week_number_string, reporting_web_path, z_bad_reporter, z_week_number_string, reporting_web_path) 
	message = message +  "<STRONG>Date : </STRONG>%s<BR>\n" % (z_today)
	message = message +  "<HR>\n"
	message = message +  "URL : <A HREF=\"%s\">MyReporting web page</A> <BR>\n" % (reporting_web_path)
	message = message +  "For any request <A HREF=\"mailto:%s\">email me</A> <BR>\n" % (z_superreporter)

	return message

### Main program

if __name__ == '__main__':
	data_dir = reporting_data_path

	year = string.atoi (strftime ("%Y", localtime(time())))
	if len (sys.argv) > 1 :
		if len (sys.argv) > 2 :
			week_number = string.atoi (sys.argv [1])
			email_mode_name = sys.argv [2]
		else:
			email_mode_name = sys.argv [1]
			week_number = string.atoi (strftime ("%W", localtime(time())) ) 
			#note: week_number: [0..53] week starts on monday ...

			week_day = string.atoi (strftime ("%w", localtime(time())) ) 
			#note: week_day: 0:sun; 1:mon; 2:tue; 3:wed; 4:thu; 5:fri; 6:sat

			#print ("===> week_number=%d -> week_day=%d \n" % (week_number, week_day))
			if email_mode_name == email_mode_remind :
				if week_day == 0 or week_day == 1 or week_day == 2:
					# if today is sun,mon,tue
					# send reminder for previous week 
					week_number = week_number - 1
				#else:
					# otherwise this is for current week 
			else: #send reports
				if week_day == 1 or week_day == 2 or week_day == 3 or week_day == 4:
					# if today is mon,tue,wed,thu
					# send reports of previous week
					week_number = week_number - 1
				#else:
					# otherwise this is for current week 
					# sent on fri,sat, or sun
			if week_number == 0 :
				week_number = 52
				year = year - 1

			#print ("===> week_number=%d -> week_day=%d \n" % (week_number, week_day))
	else:
		print "Usage: script {week_number} (new|refresh|remind)\n"
		sys.exit ();
			
	#else :
	#	week_number = string.atoi (strftime ("%U", localtime(time())) ) 
	#	email_mode_name = "new"

	week_number_string = "%i" % (week_number)
	#print "Week = %s \n" %(week_number_string)

	if (len (week_number_string) == 1) :
		week_number_string = "0" + week_number_string
	elif (len (week_number_string) > 2):
		print "Error week number %i not valid" % (week_number)
		sys.exit ();

	week_url = reporting_web_path + "data/reports/%i/week-%s.html" %(year, week_number_string)

	reporters_file = reporters_file

	dir_path = "%s/data/reports/%i" % (data_dir, year)

	week_filename = "%s/week-%s.html" % (dir_path, week_number_string)

	dir_list = os.listdir (dir_path)

	regexp = "([a-zA-Z]+)_%s\.html" % (week_number_string)
	p = re.compile (regexp);


	active_reporters = ActiveUsers (reporters_file)

	good_reporters = []
	for file in dir_list:
		result = p.search (file,0)
		if result:
			good_reporters.append (result.group (1))

	bad_reporters = []
	for reporter in active_reporters :
		found = 0
		for good in good_reporters:
			found = found or (good == reporter)
		if not found:
			bad_reporters.append (reporter)


	# Build the mail content

	if email_mode_name == email_mode_new :
		message = weekMailContent (0, good_reporters, bad_reporters, week_number_string, week_url, week_filename, reporters_email, superreporter_email)
		sendMailToFromSubjectOfOn (reporters_email, sender_name, sender_email,  message, smtp_server)
		#print message;
	if email_mode_name == email_mode_report :
		message = weekMailContent (1, good_reporters, bad_reporters, week_number_string, week_url, week_filename, reporters_email, superreporter_email)
		sendMailToFromSubjectOfOn (reporters_email, sender_name, sender_email,  message, smtp_server)
		#print message;

	if email_mode_name == email_mode_remind :
		summary_bad = "Week " + week_number_string + "\n";
		for bad_reporter in bad_reporters:
			#print "SendMail to " + bad_reporter
			summary_bad = summary_bad + "SendMail to " + bad_reporter + "\n";
			bad_reporter_email = "%s%s" % (bad_reporter, at_domain_name)
			message = badReporterMailContent (bad_reporter_email, week_number_string, week_url, bad_reporter_email, superreporter_email)
			sendMailToFromSubjectOfOn (bad_reporter_email, sender_name, sender_email, message, smtp_server)

		# Send summary to superreporter_email
		if enable_copy_to_superreporter:
			print summary_bad;
			#For sys admin ...
			sendMailToFromSubjectOfOn (superreporter_email, sender_name, sender_email, summary_bad, smtp_server)

		
