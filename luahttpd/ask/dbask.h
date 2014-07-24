// Created by Nijie on 2014.07.23.
// Copyright (c) 2014 Nijie. All rights reserved.
// Use of this source code is governed by a GPL-2 license that can be found in the LICENSE file. 
//
#ifndef __DBASK_H_NIJIE_2014_0613__
#define __DBASK_H_NIJIE_2014_0613__

#include "fxdb.h"
#include "luaask.h"
#include <string>

using namespace std;

struct SDBMysqlSN 
{
	int		nBaseSN;
	unsigned short wCount;
};

class DBAsk : public IQuery, public LuaAsk
{
public:
	DBAsk();
	virtual ~DBAsk();

	virtual INT32       GetDBId(void);
	virtual void		OnQuery(IDBConnection *poDBConnection);
	virtual void        OnResult(void);

	virtual void        Release(void);

	void				setNeedResult(bool bNeedResult);

	// lua export start
	bool				setSN(int sn);
	bool				setSQL(const char* pDBName, const char* pSql);

	unsigned int		count();
	bool				begin();
	bool				next();
	const char*			get(unsigned int dwIndex);
	int					getSize(unsigned int dwIndex);
	// lua export end

private:
	SDBMysqlSN			m_baseSN;
	bool				m_bMakeSN;
	bool				m_bNeedResult;	// �Ƿ���Ҫ�����
	INT32				m_sn;
	INT32				m_nResult;
	IDataReader*		m_pResult;
	string				m_strSQL;
};

#endif	// __DBASK_H_NIJIE_2014_0613__
