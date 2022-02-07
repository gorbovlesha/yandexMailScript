UC02_check_email()
{
	
int i = 0;

	lr_start_transaction("UC02_check_email");
	
	lr_start_transaction("UC02_T01_redirect");

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
	
	lr_end_transaction("UC02_T01_redirect", LR_AUTO);
	
	lr_think_time({ThinkTime});
	
	while (i < atoi(lr_eval_string("{messageOrThreadIdCount_count}"))) {
		
		lr_start_transaction("UC02_T02_inbox");

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
		
		lr_end_transaction("UC02_T02_inbox", LR_AUTO);
		
		lr_think_time({ThinkTime});

		lr_start_transaction("UC02_T03_read_message");
		
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

		lr_end_transaction("UC02_T03_read_message", LR_AUTO);
		
		lr_think_time({ThinkTime});
		
		lr_start_transaction("UC02_T04_inbox");

		
		web_url("inbox_4", 
			"URL={PROTOCOL}://{HOST_MAIL_YANDEX}/?message/{messageId}", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={PROTOCOL}://{HOST_MAIL_YANDEX}/lite/inbox", 
			"Snapshot=t475.inf", 
			"Mode=HTML", 
			EXTRARES, 
			LAST);
		
		lr_end_transaction("UC02_T04_inbox", LR_AUTO);
		
		lr_think_time({ThinkTime});

		i = i + 1;
	}
	
	lr_end_transaction("UC02_check_email", LR_AUTO);
		
	return 0;
}