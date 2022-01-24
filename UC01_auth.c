UC01_auth()
{
	int i = 0;
	web_set_max_html_param_len("400000");
	web_cache_cleanup();
	web_cleanup_cookies();
 	web_cleanup_auto_headers();
 	

	lr_start_transaction("UC01_auth");
	
	lr_start_transaction("UC01_T01_open_auth_page");
	
	web_reg_save_param_ex(
		"ParamName=csfr_token", 
		"LB/IC=csrf_token\" value=\"",
		"RB/IC=\"",
		SEARCH_FILTERS,
			"Scope=body",
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=process_uuid", 
		"LB/IC=login&process_uuid=",
		"RB/IC=\"",
		SEARCH_FILTERS,
			"Scope=body",
		LAST); 
	
	web_url("auth", 
		"URL={PROTOCOL}://{HOST_PASSPORT_YANDEX}/auth/welcome?origin=home_desktop_ru&retpath={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F&backpath={PROTOCOL}%3A%2F%2Fyandex.ru", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={PROTOCOL}://yandex.ru/", 
		"Snapshot=t318.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_think_time(2);

	
	lr_end_transaction("UC01_T01_open_auth_page", LR_AUTO);

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");
	
	lr_start_transaction("UC01_T02_start_auth");
		
	web_reg_save_param_regexp(
		"ParamName=track_id",
		"RegExp=\"track_id\":\"(.*?)\"",
		SEARCH_FILTERS,
		"IgnoreRedirections=0",
		"Scope=Body",
		"Group=1",
		LAST);

	web_submit_data("start", 
		"Action={PROTOCOL}://{HOST_PASSPORT_YANDEX}/registration-validations/auth/multi_step/start", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer={PROTOCOL}://{HOST_PASSPORT_YANDEX}/auth/welcome?origin=home_desktop_ru&retpath={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F&backpath={PROTOCOL}%3A%2F%2Fyandex.ru", 
		"Snapshot=t327.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={csfr_token}", ENDITEM, 
		"Name=login", "Value={login}", ENDITEM, 
		"Name=process_uuid", "Value={process_uuid}", ENDITEM, 
		"Name=track_id", "Value=", ENDITEM,
		"Name=retpath", "Value={PROTOCOL}://{HOST_MAIL_YANDEX}/", ENDITEM, 
		"Name=origin", "Value=home_desktop_ru", ENDITEM, 
		LAST);
	
	lr_think_time(2);

	lr_end_transaction("UC01_T02_start_auth", LR_AUTO);
	
	lr_start_transaction("UC01_T03_commit_password");
	
	web_submit_data("commit_password", 
		"Action={PROTOCOL}://{HOST_PASSPORT_YANDEX}/registration-validations/auth/multi_step/commit_password", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer={PROTOCOL}://{HOST_PASSPORT_YANDEX}/auth/welcome?origin=home_desktop_ru&retpath={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F&backpath={PROTOCOL}%3A%2F%2Fyandex.ru", 
		"Snapshot=t333.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={csfr_token}", ENDITEM, 
		"Name=track_id", "Value={track_id}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=retpath", "Value={PROTOCOL}://{HOST_MAIL_YANDEX}/", ENDITEM, 
		LAST);
	
	lr_think_time(2);

	lr_end_transaction("UC01_T03_commit_password", LR_AUTO);
	
	lr_start_transaction("UC01_T04_redirect");

	web_url("redirect", 
		"URL={PROTOCOL}://{HOST_PASSPORT_YANDEX}/redirect?url={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={PROTOCOL}://{HOST_PASSPORT_YANDEX}/auth/list?origin=home_desktop_ru&retpath={PROTOCOL}%3A%2F%2F{HOST_MAIL_YANDEX}%2F&backpath={PROTOCOL}%3A%2F%2Fyandex.ru&mode=edit", 
		"Snapshot=t337.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
	
	lr_think_time(2);

	lr_end_transaction("UC01_T04_redirect", LR_AUTO);

	lr_end_transaction("UC01_auth", LR_AUTO);
	
	return 0;
}