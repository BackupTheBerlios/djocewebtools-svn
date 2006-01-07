<html>
	<head>
		<title>{$VAR_HEADER_TITLE}</title>
		<link href='style/reporting.css' rel='stylesheet' type='text/css'>
	</head>
	<body>
		<div id="header">... {$VAR_APPLICATION_TITLE} ... 
			<br/>
			<span style="font-style: italic; color: #ffff88; font-size: 12;">Welcome {$VAR_REPORTER_NAME} :: {$VAR_REPORTER_TEAM}</span>
		</div>
		<table border=0 width='100%' height='100%' cellpadding="0" cellspacing="0">
			<tr height=0 >
				<td width='16%'/> 
				<td width='84%'/>
			</tr>
			<tr height='100%'>
				<td class='menu'>
					{include file=$PageMenuSrc}
				</td>
				<td class='main'>
					<div class="apptitle">{$VAR_APPLICATION_NAME}</div>
					{include file=$PageMainSrc}
				</td>
			</tr>
		</table>
	</body>
</html>
