UC03_answer()
{
	lr_start_transaction("UC03_answer");

	lr_start_transaction("UC03_T01_redirect");
	
	int i = 0;
	
	web_reg_save_param_ex(
		"ParamName=messageOrThreadIdCount", 
		"LB/IC=<a href=\"\/lite\/",
		"RB/IC=\/new\" class=\"b-messages__message__link\" aria-label=\"Test1",
		"Ordinal=All",
		SEARCH_FILTERS,
		"IgnoreRedirections=0", //added
		"Scope=body",
		LAST);
	

	web_url("redirect", 
		"URL={PROTOCOL}://{HOST_PASSPORT_YANDEX}/redirect?url={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={PROTOCOL}://{HOST_PASSPORT_YANDEX}/auth/list?origin=home_desktop_ru&retpath={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F&backpath={PROTOCOL}%3A%2F%2Fyandex.ru&mode=edit", 
		"Snapshot=t337.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
	
	lr_end_transaction("UC03_T01_redirect", LR_AUTO);
	
	lr_think_time({ThinkTime});

	while (i < atoi(lr_eval_string("{messageOrThreadIdCount_count}"))) {
		
		lr_start_transaction("UC03_T02_inbox");

		web_reg_save_param_regexp(
			"ParamName=messageId",
			"RegExp=<a href=\"\/lite(\/message|\/thread)\/(\\d*?)\/new\" class=\"b-messages__message__link\" aria-label=\"Test1",
			SEARCH_FILTERS,
			"IgnoreRedirections=0",
			"Scope=Body",
			"Group=2",
			LAST);
		
		web_url("inbox_4", 
			"URL={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/inbox", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={PROTOCOL}://{HOST_PASSPORT_YANDEX}/redirect?url={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F", 
			"Snapshot=t475.inf", 
			"Mode=HTML", 
			EXTRARES, 
			LAST);

		lr_end_transaction("UC03_T02_inbox", LR_AUTO);
		
		lr_think_time({ThinkTime});

		lr_start_transaction("UC03_T03_read_message");
			
		web_reg_save_param_ex(
			"ParamName=ckey", 
			"LB/IC=_ckey\" value=\"",
			"RB/IC=\"",
			"Ordinal=1",
			SEARCH_FILTERS,
			"IgnoreRedirections=0",
			"Scope=body",
			LAST);
			
			
		web_url("{messageId}", 
			"URL={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/message/{messageId}/new", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={PROTOCOL}://{HOST_MAIL_YANDEX}/lite",
			"Snapshot=t475.inf", 
			"Mode=HTML", 
			EXTRARES, 
			LAST);

		lr_end_transaction("UC03_T03_read_message", LR_AUTO);
		
		lr_think_time({ThinkTime});
		
		lr_start_transaction("UC03_T04_compose_message");
			
		web_reg_save_param_regexp(
			"ParamName=nameTo",
			"RegExp=name=\"to\".*? value='(.*?) &",
			SEARCH_FILTERS,
			"IgnoreRedirections=0",
			"Scope=Body",
			"Group=1",
			LAST);
			
		web_reg_save_param_regexp(
			"ParamName=emailTo",
			"RegExp=name=\"to\".*? value=\'.*? &lt;(.*?)&gt",
			SEARCH_FILTERS,
			"IgnoreRedirections=0",
			"Scope=Body",
			"Group=1",
			LAST);
		
		web_url("compose", 
			"URL={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose?oper=reply&ids={messageId}&retpath=%2Fmessage%2F{messageId}3%2Fnew", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/message/{messageId}", 
			"Snapshot=t519.inf", 
			"Mode=HTML", 
			LAST);

		lr_end_transaction("UC03_T04_compose_message", LR_AUTO);
		
		lr_think_time({ThinkTime});
		
		lr_start_transaction("UC03_T05_send_message");
		
		web_submit_data("compose-action.xml", 
			"Action={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose-action.xml", 
			"Method=POST", 
			"EncType=multipart/form-data", 
			"RecContentType=text/html", 
			"Referer={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose?oper=reply&ids={messageId}&retpath=%2Fmessage%2F{messageId}3%2Fnew", //{PROTOCOL}://{HOST_MAIL_YANDEX}/lite/compose/retpath=%2Finbox
			"Snapshot=t491.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=request", "Value=", ENDITEM, 
			"Name=to", "Value={nameTo} <{emailTo}>", ENDITEM, 
			"Name=cc", "Value=", ENDITEM, 
			"Name=bcc", "Value=", ENDITEM, 
			"Name=subj", "Value={messageHeader}", ENDITEM, 
			"Name=send", "Value={messageText}", ENDITEM, 
			"Name=att", "Value=", "File=Yes", ENDITEM, 
			"Name=doit", "Value=Отправить", ENDITEM, 
			"Name=compose_check", "Value=9a12286a32f53d22bc898e657167a347", ENDITEM, 
	        "Name=_ckey", "Value={ckey}", ENDITEM,
			"Name=ttype", "Value=plain", ENDITEM, 
			"Name=oper", "Value=reply", ENDITEM,
			"Name=_handlers", "Value=do-send", ENDITEM, 
			"Name=style", "Value=lite", ENDITEM, 
			"Name=fid", "Value=", ENDITEM, 
			"Name=from_mailbox", "Value={login}@yandex.ru", ENDITEM, 
			"Name=from_name", "Value=Gorbov", ENDITEM, 
			"Name=mark_as", "Value=replied", ENDITEM, 
			"Name=mark_ids", "Value={messageId}", ENDITEM, 
			"Name=retpath", "Value=inbox", ENDITEM, 
			"Name=nohl", "Value=", ENDITEM, 
			LAST);
		
		lr_end_transaction("UC03_T05_send_message", LR_AUTO);

	
			i = i + 1;
	}
	
	lr_end_transaction("UC03_answer", LR_AUTO);
	
	return 0;
}
