<HTML>
	<HEAD>
		<TITLE>{$VAR_HEADER_TITLE}</TITLE>
		<LINK HREF='style/reporting.css' rel='stylesheet' type='text/css'>
	</HEAD>
	<BODY>
		<TABLE border=0 width='100%' height='100%'>
			<TR HEIGHT='0'>
			<TD  COLSPAN=3 class='header'>... {$VAR_APPLICATION_TITLE} ... 
			<BR><SPAN style="font-style: italic; color: #ffff88; font-size: 12;">Welcome {$VAR_REPORTER_NAME} :: {$VAR_REPORTER_TEAM}</SPAN></TD>
			</TR>
			<TR HEIGHT=0 >
				<TD width='16%'/> 
				<TD width='84%'/>
			</TR>
			<TR HEIGHT='100%'>
				<TD class='menu'>
					{include file=$PageMenuSrc}
				</TD>
				<TD class='main'>
					<DIV class="apptitle">{$VAR_APPLICATION_NAME}</DIV>
					{include file=$PageMainSrc}
				</TD>
			</TR>
		</TABLE>
	</BODY>
</HTML>

