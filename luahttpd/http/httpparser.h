// Created by Nijie on 2014.07.23.
// Copyright (c) 2014 Nijie. All rights reserved.
// Use of this source code is governed by a GPL-2 license that can be found in the LICENSE file. 
//
#ifndef __HTTPPARSER_H_NIJIE_2013_1120__
#define __HTTPPARSER_H_NIJIE_2013_1120__

#include "match.h"
#include <string>

using namespace std;

enum EHttpRequestType
{
	HTTP_HEAD_URL = 0,
	HTTP_HEAD_GET,
	HTTP_HEAD_POST,
	HTTP_HEAD_HTTP,
	HTTP_HEAD_ACCEPT,
	HTTP_HEAD_ACCEPT_CHARSET,
	HTTP_HEAD_ACCEPT_ENCODING,
	HTTP_HEAD_ACCEPT_LANGUAGE,	// ������ɽ��ܵ����� Accept-Language: en,zh 
	HTTP_HEAD_ACCEPT_RANGES,	// ����������ҳʵ���һ�����߶���ӷ�Χ�ֶ� Accept-Ranges: bytes 
	HTTP_HEAD_AUTHORIZATION,	// HTTP��Ȩ����Ȩ֤�� Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ== 
	HTTP_HEAD_CACHE_CONTROL,	// ָ���������Ӧ��ѭ�Ļ������ Cache-Control: no-cache 
	HTTP_HEAD_CONNECTION,		// ��ʾ�Ƿ���Ҫ�־����ӡ���HTTP 1.1Ĭ�Ͻ��г־����ӣ� Connection: close 
	HTTP_HEAD_COOKIE,			//  HTTP������ʱ����ѱ����ڸ����������µ�����cookieֵһ���͸�web�������� Cookie: $Version=1; Skin=new; 
	HTTP_HEAD_CONTENT_LENGTH,	// ��������ݳ��� Content-Length: 348 
	HTTP_HEAD_CONTENT_TYPE,		// �������ʵ���Ӧ��MIME��Ϣ Content-Type: application/x-www-form-urlencoded 
	HTTP_HEAD_DATE,				// �����͵����ں�ʱ�� Date: Tue, 15 Nov 2010 08:12:31 GMT 
	HTTP_HEAD_EXPECT,			// ������ض��ķ�������Ϊ Expect: 100-continue 
	HTTP_HEAD_FROM,				// ����������û���Email From: user@email.com 
	HTTP_HEAD_HOST,				// ָ������ķ������������Ͷ˿ں� Host: www.zcmhi.com 
	HTTP_HEAD_IF_MATCH,			//	ֻ������������ʵ����ƥ�����Ч If-Match: ��737060cd8c284d8af7ad3082f209582d�� 
	HTTP_HEAD_IF_MODIFIED_SINCE,// �������Ĳ�����ָ��ʱ��֮���޸�������ɹ���δ���޸��򷵻�304���� If-Modified-Since: Sat, 29 Oct 2010 19:43:31 GMT 
	HTTP_HEAD_IF_NONE_MATCH,	// �������δ�ı䷵��304���룬����Ϊ��������ǰ���͵�Etag�����������Ӧ��Etag�Ƚ��ж��Ƿ�ı� If-None-Match: ��737060cd8c284d8af7ad3082f209582d�� 
	HTTP_HEAD_IF_RANGE,			// ���ʵ��δ�ı䣬���������Ϳͻ��˶�ʧ�Ĳ��֣�����������ʵ�塣����ҲΪEtag If-Range: ��737060cd8c284d8af7ad3082f209582d�� 
	HTTP_HEAD_IF_UNMODIFIED_SINCE,// ֻ��ʵ����ָ��ʱ��֮��δ���޸Ĳ�����ɹ� If-Unmodified-Since: Sat, 29 Oct 2010 19:43:31 GMT 
	HTTP_HEAD_MAX_FORWARDS,		// ������Ϣͨ����������ش��͵�ʱ�� Max-Forwards: 10 
	HTTP_HEAD_PRAGMA,			// ��������ʵ���ض���ָ�� Pragma: no-cache 
	HTTP_HEAD_PROXY_AUTHORIZATION,// ���ӵ��������Ȩ֤�� Proxy-Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ== 
	HTTP_HEAD_RANGE,			// ֻ����ʵ���һ���֣�ָ����Χ Range: bytes=500-999 
	HTTP_HEAD_REFERER,			// ��ǰ��ҳ�ĵ�ַ����ǰ������ҳ�������,����· Referer: http://www.zcmhi.com/archives/71.html 
	HTTP_HEAD_TE,				// �ͻ���Ը����ܵĴ�����룬��֪ͨ���������ܽ���β��ͷ��Ϣ TE: trailers,deflate;q=0.5 
	HTTP_HEAD_UPGRADE,			// �������ָ��ĳ�ִ���Э���Ա����������ת�������֧�֣� Upgrade: HTTP/2.0, SHTTP/1.3, IRC/6.9, RTA/x11 
	HTTP_HEAD_USER_AGENT,		// User-Agent�����ݰ�������������û���Ϣ User-Agent: Mozilla/5.0 (Linux; X11) 
	HTTP_HEAD_VIA,				// ֪ͨ�м����ػ�����������ַ��ͨ��Э�� Via: 1.0 fred, 1.1 nowhere.com (Apache/1.1) 
	HTTP_HEAD_WARNING,			// ������Ϣʵ��ľ�����Ϣ Warn: 199 Miscellaneous warning 
	HTTP_HEAD_POST_DATA,		// Post data

	HTTP_HEAD_SIZE,
};

typedef int (*FN_HTTP_HEAD_PARSE)(string& strVal, const char* pszBuf);

class HttpParser
{
public:
	HttpParser();
	~HttpParser();

	static bool		Init();
	
	static int		ParseHttpHeadSpace(string& strVal, const char* pszBuf);
	static int		ParseHttpHeadLRN(string& strVal, const char* pszBuf);

	bool			parse(const char* pszBuf);
	void			reset();

	string&			get(int type);

	void			debugOut();

private:
	static MatchTree*	ms_pMatchTree;
	static FN_HTTP_HEAD_PARSE ms_arFuns[HTTP_HEAD_SIZE];

	string			m_arValue[HTTP_HEAD_SIZE];
};

#endif	// __HTTPPARSER_H_NIJIE_2013_1120__
