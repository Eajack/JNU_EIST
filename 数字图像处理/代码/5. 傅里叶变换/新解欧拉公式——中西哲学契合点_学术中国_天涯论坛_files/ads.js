/**  
 * @fileOverview 无阻塞加载传漾广告脚本文件 限制 健康医疗(16)，文学/校园分类(19)
 * @author klark
 * @date 2013-10-14  
 */ 

(function($, adsGlobal, adsKeyDict){

	var CONST = {
			ADS_LOC_SELECTOR	:	'div.ads-loc-holder',//广告位div的特殊样式
			ADSAME_HOST	:	'http://dol.tianya.cn'
	},
	groupId = adsKeyDict[adsGlobal['itemId']],//分类标识
	pageType = adsGlobal['pageType'],//页面类型标识
	cacheADsLoc = [],//页面上传漾广告位节点缓存数组
	cacheADsLocDict = {},////页面上传漾广告位节点缓存字典
	adsLocLen = -1,//广告位长度
	i = 0,
	tmp,//临时变量，临时使用
	typesADsID = {
			c	:	[],//用于合并广告位脚本的广告位ID
			la	:	[]//用于单独请求的广告位ID
	};
	
	//扩展adsGlobal对象，用于传漾脚本调用
	$.extend(adsGlobal, {
		/**
		 * @param {String} adsameID 传漾广告位ID
		 * @returns {Object} 原生DOM节点或NULL
		 */
		qNode	:	function(adsameID){
			return cacheADsLocDict['_' + adsameID] ? cacheADsLocDict['_' + adsameID].node : null;
		}
	});
	
	
	
	/**
	 * 查找页面上的所有传漾广告位
	 * @returns {Array}
	 */
	function queryADsLoc(){
		var rt = [], tmp, reg = /0101$|0206$/;
		
		if(groupId){
			$(CONST.ADS_LOC_SELECTOR).each(function(i){
				var loc = $(this), type = loc.attr('data-ads-type');
				tmp = {
						node		:	loc.get(0),//广告位DOM节点
						locID		: 	loc.attr('id'),//广告位ID属性值
						adsameID	:	groupId + pageType + loc.attr('data-ads-order'),//传漾广告位ID
						adsameType	:	0 
				};
				
				//处理单独广告位
				if(reg.test( tmp.adsameID )){
					tmp.adsameType = 1;
				}
				
				rt.push(tmp);
			});
			
			//排序
			rt.sort(function(a, b){
				return a.adsameID > b.adsameID;
			});
		}

		return	rt;
	}
	
	var loadScript = (function(){
	    var adQueue = [];
	   
	 
	    function LoadADScript(url, container, init, callback){
	        this.url = url;
	        this.containerObj = ( typeof container == 'string' ? document.getElementById(container) : container );
	        this.init = init ||  function(){};  
	        this.callback = callback ||  function(){};  
	    }  
	 
	    LoadADScript.prototype = {
	        startLoad : function(){
	            var script = document.createElement('script'), _this = this;
	            
	            try {
	            	_this.init.apply();
				} catch (e) {}
	            
	            if(script.readyState){//IE
	                script.onreadystatechange = function(){
	                    if(script.readyState == 'loaded' || script.readyState == 'complete'){
	                        script.onreadystatechange = null;
	                        _this.finished();
	                    }
	                };
	            }else{//Other
	                script.onload = function(){
	                    _this.finished();
	                };
	                script.onerror = function(){
	                	_this.finished();
	                };
	            }
	 
	            script.src = _this.url;
	            script.type = 'text/javascript';
	            document.getElementsByTagName('head')[0].appendChild(script);
	        },
	        finished : function(){
	        	try{
	            	this.callback.apply();
				}catch(e){}
				
				TY.util.console(this.url);
	        }
	    };  
	 
	    return {
	    	/**
	    	 * @public
	    	 * 增加广告脚本
	    	 * @param {Object} adObj 广告参数
	    	 * adObj参数说明:
	    	 * {String} adObj.url 广告脚本文件地址
	    	 * {String|Object} adObj.container 广告位ID或广告位DOM节点
	    	 * {Function} adObj.init 脚本加载前初始化函数
	    	 * {Function} adObj.callback 脚本加载后回调函数
	    	 */
	        add : function(adObj) {
	            if(adObj){
	            	adQueue.push(new LoadADScript(adObj.url, adObj.container, adObj.init, adObj.callback));
	            }
	            return this;
	        },
	        
	        /**
	         * @public
	         * 执行广告脚本
	         */
	        execute : function() {
	        	var tmp;
	            while( (tmp = adQueue.shift()) ){
	            	tmp.startLoad();
	            }
	        }

	    };  
	}());

	
	/**
	 * ======================
	 * 初始化启动脚本代码
	 * ======================
	 */
	//没有分类，放弃. 限制在16,19
	if(!groupId || '16,19'.indexOf(groupId) == -1){
		return;
	}
	
	
	cacheADsLoc = queryADsLoc();
	adsLocLen = cacheADsLoc.length;
	for(i = 0; i < adsLocLen; i++){
		tmp = cacheADsLoc[i];
		cacheADsLocDict['_' + tmp.adsameID] = tmp;
		if(tmp.adsameType == 1){
			typesADsID.la.push( tmp.adsameID );
		}else{
			typesADsID.c.push( tmp.adsameID );
		}
	}
	
	//页面上没有传漾广告位
	if(adsLocLen == 0){
		return;
	}else{
		//加载合并广告位脚本
		if(typesADsID.c.length != 0){
			loadScript.add({
				url	:	CONST.ADSAME_HOST + '/s?z=tianya&c=' + typesADsID.c.join(',')
			});
		}
		
		//加载单独广告位脚本
		if(typesADsID.la.length != 0){
			for(i = 0; i < typesADsID.la.length; i++){
				loadScript.add({
					url	:	CONST.ADSAME_HOST + '/s?z=tianya&la=' + typesADsID.la[i]
				});
			}
		}
		
		//执行加载
		loadScript.execute();
	}
	
})(jQuery, adsGlobal, ADS_KEY_DICT);