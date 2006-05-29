{$VAR_USERS_MESSAGE|default:""}
<TABLE width=100% bgcolor=#ffffff cellpadding=0 cellspacing=2 border=0>
{foreach from=$Users item=u}
{if $u->state}
	{assign var=fontcolor value="#000000"}
{else}
	{assign var=fontcolor value="#aaaaaa"}
{/if}
<TR STYLE="color:#000000; background-color: #eeeeee" >
<TR STYLE="color: {$fontcolor}; background-color:{cycle values="#ffffff,#eeeeee"};" >
<TD><b>{$u->login}</b></TD>
	<TD><i>{$u->name}</i></TD>
	<TD>{$u->team}</TD>
	<TD><A HREF='{$u->homepage}'>{$u->homepage}</A></TD>
	<TD>{if $u->state}Active{else}InActive{/if}</TD>
</TR>
{/foreach}
</TABLE>
<DIV align=right>
<FORM ACTION="users.php" METHOD="POST">
<EM>Enter password to edit </EM> <INPUT TYPE=password size=8 name=admin value="">
<INPUT TYPE=submit VALUE="GO">
</FORM>
<DIV>
