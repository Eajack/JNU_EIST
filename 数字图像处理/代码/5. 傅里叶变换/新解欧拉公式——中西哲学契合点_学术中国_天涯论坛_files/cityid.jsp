





	
	function __setCookie(name, value, days, path, domain,secure){
		var expires = -1;
		if((typeof days == "number")&&(days >= 0)){
			var d = new Date();
			d.setTime(d.getTime()+(days*24*60*60*1000));
			expires = d.toGMTString();
		}
		document.cookie = name + "=" + value + ";"
			+ (expires != -1 ? " expires=" + expires + ";" : "")
			+ (path ? "path=" + path : "")
			+ (domain ? "; domain=" + domain : "")
			+ (secure ? "; secure" : "");
	}
	
	function __getCookie(/*String*/name){
		var cookieValue = null; 
        if (document.cookie && document.cookie != '') { 
            var cookies = document.cookie.split(';'); 
            for (var i = 0; i < cookies.length; i++) { 
                var cookie = cookies[i].replace(/(^\s*)|(\s*$)/g,   "");
                // Does this cookie string begin with the name we want? 
                if (cookie.substring(0, name.length + 1) == (name + '=')) { 
                    cookieValue = unescape(cookie.substring(name.length + 1)); 
                    break; 
                } 
            } 
        } 
        return cookieValue; 
	}
	
	var __stat_locationUrl=window.location.href;
	var __stat_cookieDomain = null;
	var __stat_cityId = "56";
	var __stat_cookieTime = 15;
	if(__stat_locationUrl.indexOf(".tianya.cn") >= 0){
		__stat_cookieDomain = ".tianya.cn";
	}else if(__stat_locationUrl.indexOf(".hainan.net") >= 0){
		__stat_cookieDomain = ".hainan.net";
	}


	if(__stat_cityId == "CN" || __stat_cityId == '0'){
		__stat_cookieTime = 7;
	}
	
	__setCookie("__cid",__stat_cityId,__stat_cookieTime,"/",__stat_cookieDomain,false);