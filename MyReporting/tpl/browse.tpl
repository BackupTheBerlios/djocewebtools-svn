<UL>
<P><STRONG>Today is {$smarty.now|date_format:"%B %d %Y"}</STRONG></P>
<TABLE border='0' cellpadding=4 cellspacing=1 width='90%'>
{foreach from=$ListYears key=yearKey item=yearItems}
<TR>
	<TD bgcolor='#ffffcc'>
	<strong>Reports {$yearKey}</strong></TD>
	<TD style="" bgcolor='#ffffff'>
	{if $yearItems.weeks}
		<TABLE WIDTH=100% BORDER=0 CELLPADDING=3 CELLSPACING=1 bgcolor=#dddddd>
			<TR bgcolor=#eeeeee >
				<TH align=center >Week</TH>
				<TH align=left>Period</TH>
				<TH>Status/Nota</TH>
				<TH align=left>LastModified</TH>
			</TR>
		{foreach from=$yearItems.weeks key=weekKey item=weekItem}
			<TR bgcolor=#ffffff 
				onclick="this.style.backgroundColor='#ffffbb';document.location='{$weekItem.file}'; "  
				onmouseout="this.style.backgroundColor='#ffffff'; "  
				onmouseover="this.style.backgroundColor='#ffeebb'; "
			>
				<TD align=center>
				<A HREF='{$weekItem.file}'>
					<STRONG>{$weekKey}</STRONG>
				</A>
				</TD>
				<TD>
				<A HREF='{$weekItem.file}'>
					{$weekItem.first_day} - {$weekItem.last_day}
				</A>
				</TD>
				<TD align=center style="{$VAR_BROWSE_WEEK_STYLE}"><STRONG>{$weekItem.status}&nbsp;{$weekItem.nota}</STRONG></TD>
				<TD><FONT color=#666666><SMALL>{$weekItem.last_modified}</SMALL></FONT></TD>
			</TR>
		{/foreach}
		</TABLE>
	{else}
		<A HREF='browse.php?selected_year={$yearKey}'>Click here to browse</A>
	{/if}
	</TD>
</TR>
{/foreach}
</TABLE>
<BR>
<TABLE border='0' cellpadding=4 cellspacing=1 width='90%'>
<TR>
<TD>
	<DIV width=100% style="padding: 20px; background-color: #ffffff; border: solid #aaaaaa 1pt;">
	<DIV style="margin-left: 25px;">
	Browse user's reports .... |
{foreach from=$ListUsers key=kUser item=vUser}
	<A HREF="browseuser.php?selected_user={$kUser}">{$kUser}</A>
	|
{/foreach}
	</DIV>
	</DIV>
</TD>
</TR>
</TABLE>
<BR>
<LI><A HREF='data/reports/reporting_list.html'>Reporting List</A></LI>
</UL>
