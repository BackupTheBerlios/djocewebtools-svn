<UL>
<FORM ACTION="browseuser.php" METHOD=GET>
Select here to change user {$VAR_EDIT_USERNAME_HTML_SELECT}
<INPUT TYPE=hidden NAME="selected_year" VALUE="{$SelectedYear}" />
<INPUT TYPE=submit VALUE="View" />
</FORM>

<DIV style="width: 550px; padding: 6px; text-align: left; font-size: 120%; background-color: #ffffcc; border: solid 1pt #bbbbbb; margin-bottom: 3px;">
Browse reports for {$SelectedUser->name} : [{$SelectedUser->login}]
{if !($SelectedUser->state)}
: <EM>Inactive Reporter</EM>
{/if}
</DIV>
<DIV style="width: 550px; padding: 6px; background-color: #ffffff; border: solid 1pt #bbbbbb;">
Please select year : <BR>
<DIV style="text-align: left; margin-left: 20px; padding: 10px">
{foreach from=$ListYearDirs key=kYear item=vDir}
<A STYLE="{if $SelectedYear == $kYear }text-decoration: underline; {/if} font-weight: bold;" HREF="browseuser.php?selected_user={$SelectedUser->login}&selected_year={$kYear}">{$kYear}</A>
{if $SelectedYear == $kYear }
	: 
	{if empty($ListUserReports)}
		no report ...
	{else}
		{foreach from=$ListUserReports key=kWeek item=vWeekfile}
		<A HREF="#w{$kWeek}">{$kWeek}</A> : 
		{/foreach}
	{/if}
{else}
: <SPAN style="font-size: 75%; font-style: italic; color: #999999;">click to browse</SPAN>
{/if}
<BR/>
{/foreach}
</DIV>
</DIV>

<BR>
{foreach from=$ListUserReports key=kWeek item=vWeekfile}
<DIV style="padding: 4px; text-align: left; background-color: #ffffff; border: solid 1pt #dddddd;">
<A NAME="w{$kWeek}" ></A>
<DIV style="padding: 4px; background-color: #eeeeff; font-weight: bold; border: solid 1px #dddddd;">
<A style="font-size: 60%;" HREF="#TOP">[^]</A> Week {$kWeek}
</DIV>
<DIV style="margin-left: 20px">
{$vWeekfile}
</DIV>
</DIV>
<BR>
{/foreach}

</UL>
