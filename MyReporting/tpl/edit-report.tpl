<FORM action='save.php' method='POST' ENCTYPE='multipart/form-data' NAME='editreportform' >
<TABLE border=0 width='100%' bgcolor='#ffffdd' >
<TR><TD>
	<TABLE border=0>
	<TR><TD>UserName</TD><TD><INPUT type='text' name='username' value='{$VAR_EDIT_USERNAME}'/></TD></TR>
	</TABLE>
</TD><TD>&nbsp;</TD>
<TD>
	<TABLE>
	<TR><TD>WeekNumber</TD><TD><INPUT type='text' name='week' value='{$VAR_EDIT_WEEK}'/></TD></TR>
	<TR><TD>YearNumber</TD><TD><INPUT type='text' name='year' value='{$VAR_EDIT_YEAR}'/></TD></TR>
	</TABLE>
</TD></TR>
<TR><TD colspan=3 style="color: red; font-weight: bold; background-color: #ffff66;">
{$VAR_EDIT_MESSAGE}
</TD></TR>
</TABLE>

{literal}
<script language="javascript">
<!--

// This script is deeply inspired by the phpBB code

// Startup variables
var imageTag = false;
var theSelection = false;

// Check for Browser & Platform for PC & IE specific bits
// More details from: http://www.mozilla.org/docs/web-developer/sniffer/browser_type.html
var clientPC = navigator.userAgent.toLowerCase(); // Get client info
var clientVer = parseInt(navigator.appVersion); // Get browser version

var is_ie = ((clientPC.indexOf("msie") != -1) && (clientPC.indexOf("opera") == -1));
var is_nav  = ((clientPC.indexOf('mozilla')!=-1) && (clientPC.indexOf('spoofer')==-1)
                && (clientPC.indexOf('compatible') == -1) && (clientPC.indexOf('opera')==-1)
                && (clientPC.indexOf('webtv')==-1) && (clientPC.indexOf('hotjava')==-1));

var is_moz = 0;

var is_win   = ((clientPC.indexOf("win")!=-1) || (clientPC.indexOf("16bit") != -1));
var is_mac    = (clientPC.indexOf("mac")!=-1);

style_code = new Array();
style_tags = new Array(
	'<B>','</B>',
	'<I>','</I>',
	'<UL>', '</UL>', 
	'<LI>','</LI>',
	'<QUOTE>','</QUOTE>',
	'<CODE>','</CODE>', 
	'<H1>','</H1>', 
	'<H2>','</H2>', 
	'<H3>','</H3>', 
	'<A HREF="">','</A>');

// 0:b, i , ul , li, quote, code

b_help = "Bold text: <b>text</b>  (alt+b)";
i_help = "Italic text: <i>text</i>  (alt+i)";
q_help = "Quote text: <quote>text</quote>  (alt+q)";
c_help = "Code display: <code>code</code>  (alt+c)";
l_help = "LI: <LI>text</LI> (alt+l)";
u_help = "UL: <UL>text</UL> (alt+u)";
h1_help = "UL: <UL>text</UL> (alt+1)";
h2_help = "UL: <UL>text</UL> (alt+2)";
h3_help = "UL: <UL>text</UL> (alt+3)";
w_help = "URL: <A HREF=''>text</A> (alt+w)";
a_help = "Close all open HTML tags";

// Declarations

function getarraysize(thearray) {
	for (i = 0; i < thearray.length; i++) {
		if ((thearray[i] == "undefined") || (thearray[i] == "") || (thearray[i] == null))
			return i;
		}
	return thearray.length;
}
function arraypush(thearray,value) {
	thearray[ getarraysize(thearray) ] = value;
}
function arraypop(thearray) {
	thearraysize = getarraysize(thearray);
	retval = thearray[thearraysize - 1];
	delete thearray[thearraysize - 1];
	return retval;
}


function storeCaret(textEl) {
	if (textEl.createTextRange) textEl.caretPos = document.selection.createRange().duplicate();
}

// From http://www.massless.org/mozedit/
function mozWrap(txtarea, open, close)
{
	var selLength = txtarea.textLength;
	var selStart = txtarea.selectionStart;
	var selEnd = txtarea.selectionEnd;
	if (selEnd == 1 || selEnd == 2)
		selEnd = selLength;

	var s1 = (txtarea.value).substring(0,selStart);
	var s2 = (txtarea.value).substring(selStart, selEnd)
	var s3 = (txtarea.value).substring(selEnd, selLength);
	txtarea.value = s1 + open + s2 + close + s3;
	return;
}


function helpline(w, help) {
	w.value = eval(help + "_help");
}
function TurnThisIntoStyle (style_id)
{
	//eval('document.editreportform.addstylecode'+style_id+'.value += "*"');

	var txtarea = document.editreportform.report_content;
	txtarea.focus();
	donotinsert = false;
	theSelection = false;


	if (style_id == -1) { // Close all open tags & default button names
		while (style_code[0]) {
			butnumber = arraypop(style_code) - 1;
			txtarea.value += style_tags[butnumber + 1];
			buttext = eval('document.editreportform.addstylecode' + butnumber + '.value');
			eval('document.editreportform.addstylecode' + butnumber + '.value ="' + buttext.substr(0,(buttext.length - 1)) + '"');
		}
		txtarea.focus();
		return;
	}

	if ((clientVer >= 4) && is_ie && is_win)
	{
		theSelection = document.selection.createRange().text; // Get text selection
		if (theSelection) {
			// Add tags around selection
			document.selection.createRange().text = style_tags[style_id] + theSelection + style_tags[style_id+1];
			txtarea.focus();
			theSelection = '';
			return;
		}
	}
	else if (txtarea.selectionEnd && (txtarea.selectionEnd - txtarea.selectionStart > 0))
	{
		mozWrap(txtarea, style_tags[style_id], style_tags[style_id+1]);
		return;
	}

	// Find last occurance of an open tag the same as the one just clicked
	for (i = 0; i < style_code.length; i++) {
		if (style_code[i] == style_id+1) {
			style_last = i;
			donotinsert = true;
		}
	}

	if (donotinsert) {		// Close all open tags up to the one just clicked & default button names
		while (style_code[style_last]) {
				butnumber = arraypop(style_code) - 1;
				txtarea.value += style_tags[butnumber + 1];
				buttext = eval('document.editreportform.addstylecode' + butnumber + '.value');
				eval('document.editreportform.addstylecode' + butnumber + '.value ="' + buttext.substr(0,(buttext.length - 1)) + '"');
			}
			txtarea.focus();
			return;
	} else { // Open tags
		// Open tag
		txtarea.value += style_tags[style_id];
		arraypush(style_code,style_id+1);
		eval('document.editreportform.addstylecode'+style_id+'.value += "*"');
		txtarea.focus();
		return;
	}
	storeCaret(txtarea);
}


function InsertText (target, text)
{
	if (target.createTextRange && target.caretPos) {
		var caretPos = target.caretPos;
		caretPos.text = caretPos.text.charAt(caretPos.text.length - 1) == ' ' ? text + ' ' : text;
		target.focus();
	} else {
	target.value  += text;
	target.focus();
	}
}

function AddTab(target, t)
{
	InsertText (target, "\t");
}
function AddDoubleTopic(target, t)
{
	InsertText (target, "\b<H2>"+t+"</H2>\n<UL>\n  <H3>ChangeMe</H3>\n  <UL>\n    <LI>...</LI>\n  </UL>\n</UL>\n\n");
}
function AddSingleTopic(target, t)
{
	InsertText (target, "\b<H2>"+t+"</H2>\n<UL>\n  <LI>...</LI>\n</UL>\n\n");
}
function AddSubTopic(target, t)
{
	InsertText (target, "\n  <UL>\n    <LI>...</LI>\n  </UL>\n\n");
}

-->
</script>
{/literal}

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
<TD colspan=3>
<TABLE border=0 cellpadding=2 cellspacing=0 >
<TR align=center valign=middle>
<TD style="color: black;" >Operation on selection </TD>
<TD><INPUT class='button' type="button" accesskey='1' name="addstylecode12" onMouseOver="helpline(helpbox, 'h1');" onclick="TurnThisIntoStyle(12)" value=" H1 " /></TD>
<TD><INPUT class='button' type="button" accesskey='2' name="addstylecode14" onMouseOver="helpline(helpbox, 'h2');" onclick="TurnThisIntoStyle(14)" value=" H2 " /></TD>
<TD><INPUT class='button' type="button" accesskey='3' name="addstylecode16" onMouseOver="helpline(helpbox, 'h3');" onclick="TurnThisIntoStyle(16)" value=" H3 " /></TD>
<TD><INPUT class='button' type="button" accesskey='b' name="addstylecode0"  onMouseOver="helpline(helpbox, 'b');" onclick="TurnThisIntoStyle(0)" style="font-weight: bold;" value=" B " /></TD>
<TD><INPUT class='button' type="button" accesskey='i' name="addstylecode2"  onMouseOver="helpline(helpbox, 'i');" onclick="TurnThisIntoStyle(2)" style="font-style: italic;" value=" I " /></TD>
<TD><INPUT class='button' type="button" accesskey='u' name="addstylecode4"  onMouseOver="helpline(helpbox, 'u');" onclick="TurnThisIntoStyle(4)" value=" UL " /></TD>
<TD><INPUT class='button' type="button" accesskey='l' name="addstylecode6"  onMouseOver="helpline(helpbox, 'l');" onclick="TurnThisIntoStyle(6)" value=" LI " /></TD>
<TD><INPUT class='button' type="button" accesskey='q' name="addstylecode8"  onMouseOver="helpline(helpbox, 'q');" onclick="TurnThisIntoStyle(8)" value=" QUOTE " /></TD>
<TD><INPUT class='button' type="button" accesskey='c' name="addstylecode10" onMouseOver="helpline(helpbox, 'c');" onclick="TurnThisIntoStyle(10)" value=" CODE " /></TD>
<TD><INPUT class='button' type="button" accesskey='w' name="addstylecode18" onMouseOver="helpline(helpbox, 'w');" onclick="TurnThisIntoStyle(18)" style="text-decoration: underline;" value=" URL " /></TD>
<TD nowrap="nowrap" align="right">
	<a href="javascript:TurnThisIntoStyle(-1)" class="genmed" onMouseOver="helpline(helpbox, 'a')">Close Tags</a>
</TD>
</TR>
<TR>
<TD colspan=7 ><span class="gensmall">
	<input type="text" name="helpbox" size="45" maxlength="100" style="width:450px; font-size:10px" class="helpline" value="Tip: Styles can be applied quickly to selected text." />
	</span>
</TD>
</TR>
</TABLE>
</TD></TR>
<TR>
<TD colspan=2>
<TEXTAREA cols='80' rows='25' name='report_content' onselect="storeCaret(this);" onclick="storeCaret(this);" onkeyup="storeCaret(this);">{if isset ($VAR_REPORT_TEXT)}{$VAR_REPORT_TEXT}{else}{include file="edit-report-dummy-text.tpl"}{/if}</TEXTAREA>
</TD>
<TD align=left>
<BUTTON type=button onclick="AddTab(report_content, 'AddTab');">+ InsertTabulation</BUTTON><BR>

<BUTTON type=button onclick="AddDoubleTopic(report_content, 'DoubleTopic');">+ DoubleTopic</BUTTON>
<DIV style="margin-left: 10pt; margin-top: 5pt; margin-bottom: 5pt;">
<TABLE border=0 cellpadding=1 cellspacing=0 bgcolor=Black><TR><TD>
<TABLE border=0 cellpadding=2 cellspacing=0 bgcolor=white><TR><TD  style="color:Blue; font-size: 8pt;">
&lt;H2&gt;DoubleTopic&lt;/H2&gt;<BR>
&lt;UL&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&lt;H3&gt;ChangeMe&lt;/H3&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&lt;UL&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;LI&gt;...&lt;/LI&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&lt;/UL&gt;<BR>
&lt;/UL&gt;
</TD></TR></TABLE>
</TD></TR></TABLE>
</DIV>

<BUTTON type=button onclick="AddSingleTopic(report_content, 'SingleTopic');">+ SingleTopic</BUTTON>
<DIV style="margin-left: 10pt; margin-top: 5pt; margin-bottom: 5pt;">
<TABLE border=0 cellpadding=1 cellspacing=0 bgcolor=Black><TR><TD>
<TABLE border=0 cellpadding=2 cellspacing=0 bgcolor=white><TR><TD style="color:Blue; font-size: 8pt;">
&lt;H2&gt;SingleTopic&lt;/H2&gt;<BR>
&lt;UL&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&lt;LI&gt;...&lt;/LI&gt;<BR>
&lt;/UL&gt;
</TD></TR></TABLE>
</TD></TR></TABLE>
</DIV>

<BUTTON type=button onclick="AddSubTopic(report_content, 'SubTopic');">+ SubTopic</BUTTON>
<DIV style="margin-left: 11pt; margin-top: 5pt; margin-bottom: 5pt;">
<TABLE border=0 cellpadding=1 cellspacing=0 bgcolor=Black><TR><TD>
<TABLE border=0 cellpadding=2 cellspacing=0 bgcolor=white><TR><TD style="color:Blue; font-size: 8pt;">
&nbsp;&nbsp;&nbsp;&nbsp;&lt;UL&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;LI&gt;...&lt;/LI&gt;<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&lt;/UL&gt;
</TD></TR></TABLE>
</TD></TR></TABLE>
</DIV>

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
