{literal}
<!-- tinyMCE -->
<script language="javascript" type="text/javascript" src="lib/tinymce/jscripts/tiny_mce/tiny_mce.js"></script>
<script language="javascript" type="text/javascript">
var tinyMCEmode = true;
	// Notice: The simple theme does not use all options some of them are limited to the advanced theme
	tinyMCE.init({
		mode : "exact",
		elements : "report_content",
		//auto_resize : true,
		theme : "advanced",
		theme_advanced_buttons1 : "bold,italic,underline,strikethrough,forecolor,backcolor,link,unlink,image,insertdate,inserttime,separator,formatselect",
		theme_advanced_buttons2 : "bullist,numlist,outdent,indent,separator,undo,redo,separator,preview,separator,cleanup,help,code,hr,removeformat,visualaid,charmap",
		theme_advanced_buttons3 : "",
		plugins : "table,insertdatetime,preview",
		theme_advanced_toolbar_location : "top"
	});
</script>
<!-- /tinyMCE -->
{/literal}
<FORM action='save.php' method='POST' ENCTYPE='multipart/form-data' NAME='editreportform' >
<table border=0 width='100%' bgcolor='#ffffdd' >
<tr><td>
	<table border=0>
	<tr><td>UserName</td><td><input type='text' name='username' value='{$VAR_EDIT_USERNAME}'/></td></tr>
	<tr><td>Related date</td><td><strong>{$VAR_EDIT_RELATED_DATE}</strong></td></tr>
	</table>
</td><td>&nbsp;</td>
<td>
	<table>
	<tr><td>WeekNumber</td><td><input type='text' name='week' value='{$VAR_EDIT_WEEK}'/></td></tr>
	<tr><td>YearNumber</td><td><input type='text' name='year' value='{$VAR_EDIT_YEAR}'/></td></tr>
	</table>
</td></tr>
<tr><td colspan=3 style="color: red; font-weight: bold; background-color: #ffff66;">
{$VAR_EDIT_MESSAGE}
</td></tr>
</table>

{if isset ($VAR_EDIT_READ_ONLY)}
{else}
<TABLE border=0 cellspacing=5 cellpadding=4 width='100%' bgcolor='#bbccff' >
<TR><TD COLSPAN='3' bgcolor='#eeeeee' >

<TABLE width='100%' cellspacing=3 cellpadding=3  border=0 >
<TR><TD>
<INPUT type='submit' name='op' value='SaveText'>
</TD>
<TD align='middle'>
&nbsp;
</TD>
<TD align='right'>
<INPUT type='reset' NAME='op' value='Reset'><BR>
</TR>
<TR>
<TD colspan=3>
<STRONG>NB</STRONG>: <EM>This is when you want to write your report from this web page</EM>
</TD>
</TR>
<TR>
<TD colspan=2>
<TEXTAREA cols='80' rows='25' id='report_content' name='report_content' >{if isset ($VAR_REPORT_TEXT)}{$VAR_REPORT_TEXT}{else}{include file="edit-report-dummy-text.tpl"}{/if}</TEXTAREA>
</TD>
<TD align=left>
</TD>
</TR>

</TD></TR>
</TABLE>
</TD></TR>

<TR><TD COLSPAN='3' bgcolor='#eeeeee'>
	<TABLE width='100%'>
	<TR>
	<TD colspan=3>
	<STRONG>URL</STRONG>: <EM>This is when you want to upload your report from an existing URL location</EM>
	</TD>
	</TR>
	<TR>
	<TD><INPUT TYPE='submit' NAME='op' VALUE='SaveUrl' /></TD><TD>URL</TD>
	<TD><INPUT TYPE='text' NAME='reporturl' VALUE='http://' SIZE='30'/></TD>
	</TR>
	</TABLE>
</TD></TR>
<TR><TD COLSPAN='3' bgcolor='#eeeeee'>
	<TABLE width='100%'>
	<TR>
	<TD colspan=3>
	<STRONG>FILE</STRONG>: <EM>This is when you want to upload your report from a existing local file </EM>
	</TD>
	</TR>
	<TR>
	<TD><INPUT TYPE='submit' NAME='op' VALUE='SaveFile' /></TD><TD>Local FILE</TD><TD><INPUT TYPE='hidden' NAME='MAX_FILE_SIZE' VALUE='100000' /><INPUT TYPE='file' NAME='reportlocalfile' VALUE='otot' SIZE='30'/></TD></TR>
	</TABLE>

</TD></TR>
</TABLE>
{/if}

</FORM>
