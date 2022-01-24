UC04_new_message()
{
	lr_start_transaction("UC04_new_message");
	
	lr_start_transaction("UC04_T01_compose_message");

	web_submit_data("compose-action.xml", 
		"Action={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose-action.xml", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"RecContentType=text/html", 
		"Referer={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose/retpath=%2Finbox", 
		"Snapshot=t491.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=request", "Value=", ENDITEM, 
		"Name=to", "Value={login}@yandex.ru", ENDITEM, 
		"Name=cc", "Value=", ENDITEM, 
		"Name=bcc", "Value=", ENDITEM, 
		"Name=subj", "Value={messageHeader}", ENDITEM, 
		"Name=send", "Value={messageText}", ENDITEM, 
		"Name=att", "Value=", "File=Yes", ENDITEM, 
		"Name=doit", "Value=Отправить", ENDITEM, 
		"Name=compose_check", "Value=9a12286a32f53d22bc898e657167a347", ENDITEM, 
        "Name=_ckey", "Value={ckey}", ENDITEM, 
		"Name=ttype", "Value=plain", ENDITEM, 
		"Name=_handlers", "Value=do-send", ENDITEM, 
		"Name=style", "Value=lite", ENDITEM, 
		"Name=fid", "Value=", ENDITEM, 
		"Name=from_mailbox", "Value={login}@yandex.ru", ENDITEM, 
		"Name=from_name", "Value=Gorbov", ENDITEM, 
		"Name=mark_as", "Value=", ENDITEM, 
		"Name=mark_ids", "Value=", ENDITEM, 
		"Name=retpath", "Value=inbox", ENDITEM, 
		"Name=nohl", "Value=", ENDITEM, 
		LAST);
	
	lr_think_time(2);

	lr_end_transaction("UC04_T01_compose_message", LR_AUTO);

	lr_end_transaction("UC04_new_message", LR_AUTO);
	
	return 0;
}
