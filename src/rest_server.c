#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdbool.h>
#include "mem_ops.h" // xmalloc() ,XFREE()...
#include "BSD/strsec.h" // strlcpy(), strlcat() and strnstr()
#include "libmongoose/mongoose.h" 

static const char *s_https_addr = "https://127.0.0.1:20100";  // HTTPS port



static void init_server_rest_test(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{

	if (ev == MG_EV_ACCEPT && fn_data != NULL) 
	{
    		struct mg_tls_opts opts = {
    	    	.cert = "cert/certificate.crt",     
    	    	.certkey = "cert/privateKey.key",  
    		};
    		mg_tls_init(c, &opts);

  	} else if (ev == MG_EV_HTTP_MSG) {


    	struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    		if (mg_http_match_uri(hm, "/health")) 
     			mg_http_reply(c, 200, "", "1");  

     		if (mg_http_match_uri(hm, "/test/*"))
     		{
     			printf("---\nSERVER recv:\n %s\n------\n", hm->message.ptr);
     			mg_http_reply(c, 200, "", "{\"result\": \"%.*s\"}\n", (int) hm->uri.len, hm->uri.ptr);
     		}  
    		
     }


  	(void) fn_data;
}


int main()
{
	// start lib mongoose
	struct mg_mgr mgr;                           
	mg_log_set("0");                             
	printf("\nVulnerable simple REST server\n Listening : %s\n",s_https_addr);
	mg_mgr_init(&mgr);                            
	mg_http_listen(&mgr, s_https_addr, init_server_rest_test, (void *) 1);	
	for (;;) mg_mgr_poll(&mgr, 1000);                  
	mg_mgr_free(&mgr);
	exit(0);
}
