<HTML><HEAD><TITLE>Report {$VAR_WEEK} of {$VAR_YEAR} :: {$VAR_START_DATE} -- {$VAR_END_DATE}</TITLE>
<LINK HREF='{$VAR_REPORTING_CSS_STYLE}' rel='stylesheet' type='text/css'>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="-1">
</HEAD>
<BODY>

<TABLE width='100%' class='reportheader' cellpadding=3 >
<TR>
<TD>Reports {$VAR_WEEK} of {$VAR_YEAR}<BR><SMALL>{$VAR_START_DATE} -- {$VAR_END_DATE}</SMALL></TD>
<TD class='headernavigation'> <A class=navheader HREF='{$VAR_WEEK_FILE_PREVIOUS}'>Previous</A> <A class=navheader HREF='{$VAR_WEEK_FILE_NEXT}'>Next</A><BR><SMALL>(creation: {$VAR_CREATION_DATE_TIME})</SMALL></TD>
</TR>
</TABLE>

<DIV class=infobox >
<A NAME='top'></A><STRONG>MyReporting: <A HREF='{$VAR_REPORTING_URL}'>web page</A></STRONG><BR>
<STRONG>Jump to</STRONG><BR>
{foreach from=$ListTeams item=teamItem key=teamKey}
<STRONG>{$teamKey}</STRONG> 
	{foreach from=$teamItem item=userItem key=userKey}
	|<A HREF='#{$userItem.login}'>{$userItem.name}</A> 
	{/foreach}
| <BR>
{/foreach}
</DIV>

{foreach from=$ListTeams item=teamItem key=teamKey}
<DIV class="teambar">Team :: {$teamKey}</DIV>
<DIV style="margin-left: 30px;">
{foreach from=$teamItem item=userItem key=userKey}
{php}
	$userItem = $this->get_template_vars('userItem');

	$week = $this->get_template_vars('VAR_WEEK');
	$year = $this->get_template_vars('VAR_YEAR');

	if (isset ($userItem['week_filename'])) {
		$text = processed_bots_html (ContentOfFile ($userItem['week_filename']));
		$this->assign("userText", $text);
	}
	$this->assign("VAR_USER_EDIT_REPORT", myreporting_edit_url ($userItem['login'], $year, $week) );

{/php}
<BR>
<A NAME='{$userItem.login}'/>
<TABLE width='100%' cellspacing='0' cellpadding='0'>
<TR>
<TD class='reporttitle'><A HREF="{$VAR_USER_EDIT_REPORT}"><IMG SRC="{$VAR_REPORTING_URL}/img/small_image.gif" BORDER=0></A> {$userItem.login} :: {$userItem.name} </TD>

<TD class='reportnavigation'>
<A class="nav" HREF='{$userItem.homepage}'> HomePage </A> &middot; 
<A class="nav" HREF='{$VAR_WEEK_FILE_PREVIOUS}#{$userItem.login}'> Previous </A> &middot; 
<A class="nav" HREF='{$VAR_WEEK_FILE_NEXT}#{$userItem.login}'> Next </A> &middot; 
</TD>
</TR>
</TABLE>
<TABLE width='100%'>
<TR>
<TD valign='top' width='20'><A HREF='#top' STYLE='font-size: 8pt;'>top</A></TD>
<TD class='reporttext'>{if isset($userItem.week_filename)}{$userText}{else}No report for this user !!!{/if}</TD>
</TR>
</TABLE>
{/foreach}
</DIV>
{/foreach}
</BODY></HTML>
