/* Copyright (c) 2000, 2011, Oracle and/or its affiliates. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */


/**
@file

@brief
Read language depeneded messagefile
*/

#include "sql_priv.h"
#include "unireg.h"
#include "derror.h"
#include "mysys_err.h"
#include "mysqld.h"                             // lc_messages_dir
#include "derror.h"                             // read_texts
#include "sql_class.h"                          // THD
#include "string.h"
static void init_myfunc_errs(void);

const char **server_errmsgs;

#define SERVER_SETMSG(nr, msg) server_errmsgs[(nr) - ER_ERROR_FIRST]= (msg)

#define SERVER_ERR_ERRORS            (ER_ERROR_LAST - ER_ERROR_FIRST + 1)

C_MODE_START
static const char **get_server_errmsgs()
{
	return server_errmsgs;
}
C_MODE_END

	/**
	Read messages from errorfile.

	This function can be called multiple times to reload the messages.
	If it fails to load the messages, it will fail softly by initializing
	the errmesg pointer to an array of empty strings or by keeping the
	old array if it exists.

	@retval
	FALSE       OK
	@retval
	TRUE        Error
	*/


bool init_errmessage(void)
{
	DBUG_ENTER("init_errmessage");


	if (! (server_errmsgs= (const char**) my_malloc(SERVER_ERR_ERRORS * sizeof(char*), MYF(MY_WME | MY_ZEROFILL))))
		return 1;

	if(strcmp(inception_language_code, "zh-CN")==0){
		SERVER_SETMSG(ER_ERROR_FIRST, "HelloWorld");
		SERVER_SETMSG(ER_NOT_SUPPORTED_YET, "不支持的语法类型");
		SERVER_SETMSG(ER_SQL_NO_SOURCE, "The sql have no source information.");
		SERVER_SETMSG(ER_SQL_NO_OP_TYPE, "The sql have no operation type.");
		SERVER_SETMSG(ER_SQL_INVALID_OP_TYPE, "Invalid sql operation type.");
		SERVER_SETMSG(ER_PARSE_ERROR, "%s near \'%-.80s\' at line %d");
		SERVER_SETMSG(ER_SYNTAX_ERROR, "您的SQL存在语法错误，");
		SERVER_SETMSG(ER_REMOTE_EXE_ERROR, "Execute in source server failed.");
		SERVER_SETMSG(ER_SHUTDOWN_COMPLETE, "Shutdown complete.");
		SERVER_SETMSG(ER_WITH_INSERT_FIELD, "INSERT语句请指定字段列表");
		SERVER_SETMSG(ER_WITH_INSERT_VALUES, "INSERT语句请指定值列表");
		SERVER_SETMSG(ER_WRONG_VALUE_COUNT_ON_ROW, "第 %ld 组插入数据值列表与字段列表数量不匹配");
		SERVER_SETMSG(ER_BAD_FIELD_ERROR, "字段 \'%-.192s\' 不在 \'%-.192s\' 表内");
		SERVER_SETMSG(ER_FIELD_SPECIFIED_TWICE, "插入字段 \'%-.192s\' 在 \'%-.192s\' 表内被重复指定");
		SERVER_SETMSG(ER_BAD_NULL_ERROR, "第 %d 组数据字段 \'%-.192s\' 不能为NULL");
		SERVER_SETMSG(ER_NO_WHERE_CONDITION, "请给语句加上WHERE条件");
		SERVER_SETMSG(ER_NORMAL_SHUTDOWN, "%s: Normal shutdown\n");
		SERVER_SETMSG(ER_FORCING_CLOSE, "%s: Forcing close of thread %ld  user: \'%-.48s\'\n");
		SERVER_SETMSG(ER_CON_COUNT_ERROR, "Too many connections");
		SERVER_SETMSG(ER_INVALID_COMMAND, "Invalid command.");
		SERVER_SETMSG(ER_SQL_INVALID_SOURCE, "Invalid source infomation; 审核密码不能包含*");
		SERVER_SETMSG(ER_WRONG_DB_NAME, "Incorrect database name \'%-.100s\'.");
		SERVER_SETMSG(EXIT_UNKNOWN_VARIABLE, "Exist incorrect variable.");
		SERVER_SETMSG(EXIT_UNKNOWN_OPTION, "Exist incorrect option.");
		SERVER_SETMSG(ER_NO_DB_ERROR, "请使用USE DB来指定数据库");
		SERVER_SETMSG(ER_WITH_LIMIT_CONDITION, "UPDATE/DELETE语句不能包含limit条件");
		SERVER_SETMSG(ER_WITH_ORDERBY_CONDITION, "UPDATE/DELETE语句不能包含ORDER BY条件");
		SERVER_SETMSG(ER_SELECT_ONLY_STAR, "禁止使用SELECT * 语句");
		SERVER_SETMSG(ER_ORDERY_BY_RAND, "SELECT语句禁止使用ORDER BY RAND");
		SERVER_SETMSG(ER_ID_IS_UPER, "Identifier is not allowed to been upper-case.");
		SERVER_SETMSG(ER_UNKNOWN_COLLATION, "Unknown collation: \'%-.64s\'.");
		SERVER_SETMSG(ER_INVALID_DATA_TYPE, "不支持的字段类型 \'%-.64s\'");
		SERVER_SETMSG(ER_NOT_ALLOWED_NULLABLE, "字段 \'%-.64s\' 在 \'%-.64s\' 表内不允许为NULL，请指定为NOT NULL");
		SERVER_SETMSG(ER_DUP_FIELDNAME, "字段名 \'%-.192s\' 重复 ");
		SERVER_SETMSG(ER_WRONG_COLUMN_NAME, "Incorrect column name \'%-.100s\'.");
		SERVER_SETMSG(ER_WRONG_AUTO_KEY, "Incorrect table definition; there can be only one auto column and it must be defined as a key.");
		SERVER_SETMSG(ER_TABLE_CANT_HANDLE_AUTO_INCREMENT, "The used table type doesn\'t support AUTO_INCREMENT columns.");
		SERVER_SETMSG(ER_FOREIGN_KEY, "表 \'%-.64s\' 禁止使用外键约束");
		SERVER_SETMSG(ER_TOO_MANY_KEY_PARTS, "索引 \'%-.64s\' 在 \'%-.64s\' 表内包含的列数过多, 一个索引最多允许包含 %d 列");
		SERVER_SETMSG(ER_TOO_LONG_IDENT, "Identifier name \'%-.100s\' is too long.");
		SERVER_SETMSG(ER_UDPATE_TOO_MUCH_ROWS, "预估语句影响行数超过 %d 行，仅做参考，请尽量使用主键更新");
		SERVER_SETMSG(ER_WRONG_NAME_FOR_INDEX, "Incorrect index name \'%-.100s\' in table \'%-.64s\'.");
		SERVER_SETMSG(ER_TOO_MANY_KEYS, "表 \'%-.64s\' 索引数过多, 单表最多允许创建 %d 个索引");
		SERVER_SETMSG(ER_NOT_SUPPORTED_KEY_TYPE, "不支持的索引类型: \'%-.64s\'");
		SERVER_SETMSG(ER_WRONG_SUB_KEY, "Incorrect prefix key; the used key part isn\'t a string, the used length is longer than the key part, or the storage engine doesn\'t support unique prefix keys");
		SERVER_SETMSG(ER_WRONG_KEY_COLUMN, "所使用的存储引擎不能为字段 \'%-.192s\' 创建索引");
		SERVER_SETMSG(ER_TOO_LONG_KEY, "索引 \'%-.64s\' 长度超出限制; 最大不超过 %d 字节");
		SERVER_SETMSG(ER_MULTIPLE_PRI_KEY, "定义了多个主键");
		SERVER_SETMSG(ER_DUP_KEYNAME, "索引名称重复 \'%-.192s\'");
		SERVER_SETMSG(ER_TOO_LONG_INDEX_COMMENT, "Comment for index \'%-.64s\' is too long (max = %lu).");
		SERVER_SETMSG(ER_DUP_INDEX, "索引定义重复 \'%-.64s\'");
		SERVER_SETMSG(ER_TEMP_TABLE_TMP_PREFIX, "请设置临时表的前缀为 \'tmp_\'");
		SERVER_SETMSG(ER_TABLE_MUST_INNODB, "请设置存储引擎为INNODB");
		SERVER_SETMSG(ER_TABLE_ENGINE_NOT_ALLOWED, "表 \'%-.64s\' 禁止指定存储引擎");
		SERVER_SETMSG(ER_TABLE_CHARSET_MUST_UTF8, "请给数据库/表设置字符集，仅支持\'%-.192s\'");
		SERVER_SETMSG(ER_NAMES_MUST_UTF8, "仅支持 \'%-.192s\' 字符集");
		SERVER_SETMSG(ER_TABLE_MUST_HAVE_COMMENT, "请给表 \'%-.192s\' 添加注释");
		SERVER_SETMSG(ER_COLUMN_HAVE_NO_COMMENT, "请给字段 \'%-.64s\' 添加注释");
		SERVER_SETMSG(ER_TABLE_MUST_HAVE_PK, "请给表 \'%-.64s\' 添加主键，表必须要有一个主键");
		SERVER_SETMSG(ER_PARTITION_NOT_ALLOWED, "禁止创建分区表");
		SERVER_SETMSG(ER_USE_ENUM, "Type enum is used in column.");
		SERVER_SETMSG(ER_USE_TEXT_OR_BLOB, "字段禁止使用BLOB/TEXT类型 \'%-.192s\'");
		SERVER_SETMSG(ER_COLUMN_EXISTED, "字段 \'%-.64s\' 已存在");
		SERVER_SETMSG(ER_COLUMN_NOT_EXISTED, "字段 \'%-.64s\' 不存在");
		SERVER_SETMSG(ER_CANT_DROP_FIELD_OR_KEY, "无法删除 \'%-.192s\'; 请检查字段/索引是否存在");
		SERVER_SETMSG(ER_INVALID_DEFAULT, "无效的默认值 \'%-.192s\'");
		SERVER_SETMSG(ER_USERNAME, "user name");
		SERVER_SETMSG(ER_HOSTNAME, "host name");
		SERVER_SETMSG(ER_NOT_VALID_PASSWORD, "Your password does not satisfy the current policy requirements.");
		SERVER_SETMSG(ER_WRONG_STRING_LENGTH, "String \'%-.70s\' is too long for %s (should be no longer than %d).");
		SERVER_SETMSG(ER_BLOB_USED_AS_KEY, "BLOB字段 \'%-.192s\' 不能建立索引");
		SERVER_SETMSG(ER_TOO_LONG_BAKDB_NAME, "备份库名 \'%-s-%d-%s\' 过长，建议使用别名解析");
		SERVER_SETMSG(ER_INVALID_BACKUP_HOST_INFO, "无效的备份库，请检查相关配置");
		SERVER_SETMSG(ER_BINLOG_CORRUPTED, "Binlog is corrupted.");
		SERVER_SETMSG(ER_NET_READ_ERROR, "Got an error reading communication packets.");
		SERVER_SETMSG(ER_NETWORK_READ_EVENT_CHECKSUM_FAILURE, "Replication event checksum verification failed while reading from network.");
		SERVER_SETMSG(ER_SLAVE_RELAY_LOG_WRITE_FAILURE, "Relay log write failure: %s.");
		SERVER_SETMSG(ER_INCORRECT_GLOBAL_LOCAL_VAR, "Variable \'%-.192s\' is a %s variable.");
		SERVER_SETMSG(ER_START_AS_BEGIN, "Must start as begin statement.");
		SERVER_SETMSG(ER_OUTOFMEMORY, "Out of memory; restart server and try again (needed %d bytes).");
		SERVER_SETMSG(ER_HAVE_BEGIN, "Have you begin twice? Or you didn't commit last time, if so, you can execute commit explicitly.");
		SERVER_SETMSG(ER_NET_READ_INTERRUPTED, "Got timeout reading communication packets.");
		SERVER_SETMSG(ER_BINLOG_FORMAT_STATEMENT, "The binlog_format is statement, backup is disabled.");
		SERVER_SETMSG(EXIT_NO_ARGUMENT_ALLOWED, "Not allow set argument.");
		SERVER_SETMSG(EXIT_ARGUMENT_REQUIRED, "Require argument.");
		SERVER_SETMSG(EXIT_AMBIGUOUS_OPTION, "Ambiguous argument.");
		SERVER_SETMSG(ER_ERROR_EXIST_BEFORE, "Exist error at before statement.");
		SERVER_SETMSG(ER_UNKNOWN_SYSTEM_VARIABLE, "Unknown system variable \'%-.64s\'.");
		SERVER_SETMSG(ER_UNKNOWN_CHARACTER_SET, "不支持的字符集 \'%-.64s\'");
		SERVER_SETMSG(ER_END_WITH_COMMIT, "Must end with commit.");
		SERVER_SETMSG(ER_DB_NOT_EXISTED_ERROR, "数据库 \'%-.64s\' 不存在");
		SERVER_SETMSG(ER_TABLE_EXISTS_ERROR, "表 \'%-.192s\' 已存在");
		SERVER_SETMSG(ER_INDEX_NAME_IDX_PREFIX, "普通索引 \'%-.192s\' 前缀请设置为 \'idx_\'");
		SERVER_SETMSG(ER_INDEX_NAME_UNIQ_PREFIX, "唯一索引 \'%-.192s\' 前缀请设置为 \'uniq_\'");
		SERVER_SETMSG(ER_AUTOINC_UNSIGNED, "请设置自增列为无符号类型 ");
		SERVER_SETMSG(ER_VARCHAR_TO_TEXT_LEN, "请将字段 \'%-.192s\' 设置为TEXT类型");
		SERVER_SETMSG(ER_CHAR_TO_VARCHAR_LEN, "请将字段 \'%-.192s\' 设置为VARCHAR类型");
		SERVER_SETMSG(ER_KEY_COLUMN_DOES_NOT_EXITS, "索引字段 \'%-.192s\' 不存在");
		SERVER_SETMSG(ER_INC_INIT_ERR, "请设置 AUTO_INCREMENT = 1");
		SERVER_SETMSG(ER_WRONG_ARGUMENTS, "Incorrect arguments to %s.");
		SERVER_SETMSG(ER_SET_DATA_TYPE_INT_BIGINT, "请设置自增字段为INT/BIGINT");
		SERVER_SETMSG(ER_TIMESTAMP_DEFAULT, "请为TIMESTAMP字段 \'%-.64s\' 设置默认值");
		SERVER_SETMSG(ER_CHARSET_ON_COLUMN, "禁止给字段 \'%-.64s\' 指定字符集");
		SERVER_SETMSG(ER_AUTO_INCR_ID_WARNING, "字段 \'%-.64s\' 看起来是有含义的，请提供一个与业务无关的字段作为主键");
		SERVER_SETMSG(ER_ALTER_TABLE_ONCE, "请将对表 \'%-.64s\' 的操作合并成一个ALTER语句");
		SERVER_SETMSG(ER_BLOB_CANT_HAVE_DEFAULT, "BLOB/TEXT字段 \'%-.192s\' 不支持设置默认值");
		SERVER_SETMSG(ER_END_WITH_SEMICOLON, "请以分号结尾 \';\' ");
		SERVER_SETMSG(ER_NON_UNIQ_ERROR, "Column \'%-.192s\' in %-.192s is ambiguous.");
		SERVER_SETMSG(ER_TABLE_NOT_EXISTED_ERROR, "表 \'%-.192s\' 不存在");
		SERVER_SETMSG(ER_UNKNOWN_TABLE, "Unknown table \'%-.192s\' in %-.32s.");
		SERVER_SETMSG(ER_INVALID_GROUP_FUNC_USE, "Invalid use of group function.");
		SERVER_SETMSG(ER_INDEX_USE_ALTER_TABLE, "请使用ALTER语句进行索引变更");
		SERVER_SETMSG(ER_WITH_DEFAULT_ADD_COLUMN, "建议给字段 \'%-.192s\' 添加默认值");
		SERVER_SETMSG(ER_TRUNCATED_WRONG_VALUE, "Truncated incorrect %-.32s value: \'%-.128s\'");
		SERVER_SETMSG(ER_TEXT_NOT_NULLABLE_ERROR, "TEXT/BLOB字段 \'%-.64s\' 不允许为NOT NULL");
		SERVER_SETMSG(ER_WRONG_VALUE_FOR_VAR, "Variable \'%-.64s\' can\'t be set to the value of \'%-.200s\'");
		SERVER_SETMSG(ER_TOO_MUCH_AUTO_TIMESTAMP_COLS, "Incorrect table definition; there can be only one TIMESTAMP column with CURRENT_TIMESTAMP in DEFAULT or ON UPDATE clause");
		SERVER_SETMSG(ER_INVALID_ON_UPDATE, "Invalid ON UPDATE clause for \'%-.192s\' column");
		SERVER_SETMSG(ER_DDL_DML_COEXIST, "DDL can not coexist with the DML for table \'%-.192s\'.");
		SERVER_SETMSG(ER_SLAVE_CORRUPT_EVENT, "Corrupted replication event was detected.");
		SERVER_SETMSG(ER_COLLATION_CHARSET_MISMATCH, "COLLATION \'%s\' is not valid for CHARACTER SET \'%s\'");
		SERVER_SETMSG(ER_NOT_SUPPORTED_ALTER_OPTION, "Not supported statement of alter option");
		SERVER_SETMSG(ER_CONFLICTING_DECLARATIONS, "Conflicting declarations: \'%s%s\' and \'%s%s\'");
		SERVER_SETMSG(ER_IDENT_USE_KEYWORD, "标识符 \'%s\' 是MySQL关键字/保留字，不建议使用");
		SERVER_SETMSG(ER_VIEW_SELECT_CLAUSE, "View\'s SELECT contains a \'%s\' clause");
		SERVER_SETMSG(ER_OSC_KILL_FAILED, "Can not find OSC executing task");
		SERVER_SETMSG(ER_NET_PACKETS_OUT_OF_ORDER, "Got packets out of order");
		SERVER_SETMSG(ER_NOT_SUPPORTED_ITEM_TYPE, "Not supported expression type \'%s\'.");
		SERVER_SETMSG(ER_INVALID_IDENT, "无效标识符 \'%s\' , 仅支持数字、字母、下划线: [a-z|A-Z|0-9|_]");
		SERVER_SETMSG(ER_INCEPTION_EMPTY_QUERY, "Inception error, Query was empty.");
		SERVER_SETMSG(ER_PK_COLS_NOT_INT, "字段 \'%s\' 类型不正确，请使用INT/BIGINT作为主键");
		SERVER_SETMSG(ER_PK_TOO_MANY_PARTS, "Too many primary key part in table \'%s\'.\'%s\', max parts: %d");
		SERVER_SETMSG(ER_REMOVED_SPACES, "Leading spaces are removed from name \'%s\'");
		SERVER_SETMSG(ER_ERROR_LAST, "TheLastError,ByeBye");
	} else
	{
		SERVER_SETMSG(ER_ERROR_FIRST, "HelloWorld");
		SERVER_SETMSG(ER_NOT_SUPPORTED_YET, "Not supported statement type.");
		SERVER_SETMSG(ER_SQL_NO_SOURCE, "The sql have no source information.");
		SERVER_SETMSG(ER_SQL_NO_OP_TYPE, "The sql have no operation type.");
		SERVER_SETMSG(ER_SQL_INVALID_OP_TYPE, "Invalid sql operation type.");
		SERVER_SETMSG(ER_PARSE_ERROR, "%s near \'%-.80s\' at line %d");
		SERVER_SETMSG(ER_SYNTAX_ERROR, "You have an error in your SQL syntax, ");
		SERVER_SETMSG(ER_REMOTE_EXE_ERROR, "Execute in source server failed.");
		SERVER_SETMSG(ER_SHUTDOWN_COMPLETE, "Shutdown complete.");
		SERVER_SETMSG(ER_WITH_INSERT_FIELD, "Set the field list for insert statements.");
		SERVER_SETMSG(ER_WITH_INSERT_VALUES, "Set the values list for insert statements.");
		SERVER_SETMSG(ER_WRONG_VALUE_COUNT_ON_ROW, "Column count doesn\'t match value count at row %ld.");
		SERVER_SETMSG(ER_BAD_FIELD_ERROR, "Unknown column \'%-.192s\' in \'%-.192s\'.");
		SERVER_SETMSG(ER_FIELD_SPECIFIED_TWICE, "Column \'%-.192s\' specified twice in table \'%-.192s\'.");
		SERVER_SETMSG(ER_BAD_NULL_ERROR, "Column \'%-.192s\' cannot be null in %d row.");
		SERVER_SETMSG(ER_NO_WHERE_CONDITION, "set the where condition for select statement.");
		SERVER_SETMSG(ER_NORMAL_SHUTDOWN, "%s: Normal shutdown\n");
		SERVER_SETMSG(ER_FORCING_CLOSE, "%s: Forcing close of thread %ld  user: \'%-.48s\'\n");
		SERVER_SETMSG(ER_CON_COUNT_ERROR, "Too many connections");
		SERVER_SETMSG(ER_INVALID_COMMAND, "Invalid command.");
		SERVER_SETMSG(ER_SQL_INVALID_SOURCE, "Invalid source infomation.");
		SERVER_SETMSG(ER_WRONG_DB_NAME, "Incorrect database name \'%-.100s\'.");
		SERVER_SETMSG(EXIT_UNKNOWN_VARIABLE, "Exist incorrect variable.");
		SERVER_SETMSG(EXIT_UNKNOWN_OPTION, "Exist incorrect option.");
		SERVER_SETMSG(ER_NO_DB_ERROR, "No database selected.");
		SERVER_SETMSG(ER_WITH_LIMIT_CONDITION, "Limit is not allowed in update/delete statement.");
		SERVER_SETMSG(ER_WITH_ORDERBY_CONDITION, "Order by is not allowed in update/delete statement.");
		SERVER_SETMSG(ER_SELECT_ONLY_STAR, "Select only star is not allowed.");
		SERVER_SETMSG(ER_ORDERY_BY_RAND, "Order by rand is not allowed in select statement.");
		SERVER_SETMSG(ER_ID_IS_UPER, "Identifier is not allowed to been upper-case.");
		SERVER_SETMSG(ER_UNKNOWN_COLLATION, "Unknown collation: \'%-.64s\'.");
		SERVER_SETMSG(ER_INVALID_DATA_TYPE, "Not supported data type on field: \'%-.64s\'.");
		SERVER_SETMSG(ER_NOT_ALLOWED_NULLABLE, "Column \'%-.64s\' in table \'%-.64s\' is not allowed to been nullable.");
		SERVER_SETMSG(ER_DUP_FIELDNAME, "Duplicate column name \'%-.192s\'.");
		SERVER_SETMSG(ER_WRONG_COLUMN_NAME, "Incorrect column name \'%-.100s\'.");
		SERVER_SETMSG(ER_WRONG_AUTO_KEY, "Incorrect table definition; there can be only one auto column and it must be defined as a key.");
		SERVER_SETMSG(ER_TABLE_CANT_HANDLE_AUTO_INCREMENT, "The used table type doesn\'t support AUTO_INCREMENT columns.");
		SERVER_SETMSG(ER_FOREIGN_KEY, "Foreign key is not allowed in table \'%-.64s\'.");
		SERVER_SETMSG(ER_TOO_MANY_KEY_PARTS, "Too many key parts in Key \'%-.64s\' in table \'%-.64s\' specified, max %d parts allowed.");
		SERVER_SETMSG(ER_TOO_LONG_IDENT, "Identifier name \'%-.100s\' is too long.");
		SERVER_SETMSG(ER_UDPATE_TOO_MUCH_ROWS, "Update rows more then %d.");
		SERVER_SETMSG(ER_WRONG_NAME_FOR_INDEX, "Incorrect index name \'%-.100s\' in table \'%-.64s\'.");
		SERVER_SETMSG(ER_TOO_MANY_KEYS, "Too many keys specified in table \'%-.64s\', max %d keys allowed.");
		SERVER_SETMSG(ER_NOT_SUPPORTED_KEY_TYPE, "Not supported key type: \'%-.64s\'.");
		SERVER_SETMSG(ER_WRONG_SUB_KEY, "Incorrect prefix key; the used key part isn\'t a string, the used length is longer than the key part, or the storage engine doesn\'t support unique prefix keys");
		SERVER_SETMSG(ER_WRONG_KEY_COLUMN, "The used storage engine can\'t index column \'%-.192s\'.");
		SERVER_SETMSG(ER_TOO_LONG_KEY, "Specified key \'%-.64s\' was too long; max key length is %d bytes.");
		SERVER_SETMSG(ER_MULTIPLE_PRI_KEY, "Multiple primary key defined.");
		SERVER_SETMSG(ER_DUP_KEYNAME, "Duplicate key name \'%-.192s\'.");
		SERVER_SETMSG(ER_TOO_LONG_INDEX_COMMENT, "Comment for index \'%-.64s\' is too long (max = %lu).");
		SERVER_SETMSG(ER_DUP_INDEX, "Duplicate index \'%-.64s\' defined on the table \'%-.64s.%-.64s\'.");
		SERVER_SETMSG(ER_TEMP_TABLE_TMP_PREFIX, "Set \'tmp\' prefix for temporary table.");
		SERVER_SETMSG(ER_TABLE_MUST_INNODB, "Set engine to innodb for table \'%-.64s\'.");
		SERVER_SETMSG(ER_TABLE_ENGINE_NOT_ALLOWED, "Cannot set engine for table \'%-.64s\'.");
		SERVER_SETMSG(ER_TABLE_CHARSET_MUST_UTF8, "Set charset to one of \'%-.192s\' for table \'%-.64s\'.");
		SERVER_SETMSG(ER_NAMES_MUST_UTF8, "Set charset to one of \'%-.192s\'.");
		SERVER_SETMSG(ER_TABLE_MUST_HAVE_COMMENT, "Set comments for table \'%-.192s\'.");
		SERVER_SETMSG(ER_COLUMN_HAVE_NO_COMMENT, "Column \'%-.64s\' in table \'%-.64s\' have no comments.");
		SERVER_SETMSG(ER_TABLE_MUST_HAVE_PK, "Set a primary key for table \'%-.64s\'.");
		SERVER_SETMSG(ER_PARTITION_NOT_ALLOWED, "Partition is not allowed in table.");
		SERVER_SETMSG(ER_USE_ENUM, "Type enum is used in column.");
		SERVER_SETMSG(ER_USE_TEXT_OR_BLOB, "Type blob/text is used in column \'%-.192s\'.");
		SERVER_SETMSG(ER_COLUMN_EXISTED, "Column \'%-.64s\' have existed.");
		SERVER_SETMSG(ER_COLUMN_NOT_EXISTED, "Column \'%-.64s\' not existed.");
		SERVER_SETMSG(ER_CANT_DROP_FIELD_OR_KEY, "Can\'t DROP \'%-.192s\'; check that column/key exists.");
		SERVER_SETMSG(ER_INVALID_DEFAULT, "Invalid default value for column \'%-.192s\'.");
		SERVER_SETMSG(ER_USERNAME, "user name");
		SERVER_SETMSG(ER_HOSTNAME, "host name");
		SERVER_SETMSG(ER_NOT_VALID_PASSWORD, "Your password does not satisfy the current policy requirements.");
		SERVER_SETMSG(ER_WRONG_STRING_LENGTH, "String \'%-.70s\' is too long for %s (should be no longer than %d).");
		SERVER_SETMSG(ER_BLOB_USED_AS_KEY, "BLOB column \'%-.192s\' can\'t be used in key specification with the used table type.");
		SERVER_SETMSG(ER_TOO_LONG_BAKDB_NAME, "The backup dbname \'%-s-%d-%s\' is too long.");
		SERVER_SETMSG(ER_INVALID_BACKUP_HOST_INFO, "Invalid remote backup information.");
		SERVER_SETMSG(ER_BINLOG_CORRUPTED, "Binlog is corrupted.");
		SERVER_SETMSG(ER_NET_READ_ERROR, "Got an error reading communication packets.");
		SERVER_SETMSG(ER_NETWORK_READ_EVENT_CHECKSUM_FAILURE, "Replication event checksum verification failed while reading from network.");
		SERVER_SETMSG(ER_SLAVE_RELAY_LOG_WRITE_FAILURE, "Relay log write failure: %s.");
		SERVER_SETMSG(ER_INCORRECT_GLOBAL_LOCAL_VAR, "Variable \'%-.192s\' is a %s variable.");
		SERVER_SETMSG(ER_START_AS_BEGIN, "Must start as begin statement.");
		SERVER_SETMSG(ER_OUTOFMEMORY, "Out of memory; restart server and try again (needed %d bytes).");
		SERVER_SETMSG(ER_HAVE_BEGIN, "Have you begin twice? Or you didn't commit last time, if so, you can execute commit explicitly.");
		SERVER_SETMSG(ER_NET_READ_INTERRUPTED, "Got timeout reading communication packets.");
		SERVER_SETMSG(ER_BINLOG_FORMAT_STATEMENT, "The binlog_format is statement, backup is disabled.");
		SERVER_SETMSG(EXIT_NO_ARGUMENT_ALLOWED, "Not allow set argument.");
		SERVER_SETMSG(EXIT_ARGUMENT_REQUIRED, "Require argument.");
		SERVER_SETMSG(EXIT_AMBIGUOUS_OPTION, "Ambiguous argument.");
		SERVER_SETMSG(ER_ERROR_EXIST_BEFORE, "Exist error at before statement.");
		SERVER_SETMSG(ER_UNKNOWN_SYSTEM_VARIABLE, "Unknown system variable \'%-.64s\'.");
		SERVER_SETMSG(ER_UNKNOWN_CHARACTER_SET, "Unknown character set: \'%-.64s\'.");
		SERVER_SETMSG(ER_END_WITH_COMMIT, "Must end with commit.");
		SERVER_SETMSG(ER_DB_NOT_EXISTED_ERROR, "Selected Database \'%-.64s\' not existed.");
		SERVER_SETMSG(ER_TABLE_EXISTS_ERROR, "Table \'%-.192s\' already exists.");
		SERVER_SETMSG(ER_INDEX_NAME_IDX_PREFIX, "Index \'%-.192s\' in table \'%-.64s\' need \'idx_\' prefix.");
		SERVER_SETMSG(ER_INDEX_NAME_UNIQ_PREFIX, "Index \'%-.192s\' in table \'%-.64s\' need \'uniq_\' prefix.");
		SERVER_SETMSG(ER_AUTOINC_UNSIGNED, "Set unsigned attribute on auto increment column in table \'%-.64s\'.");
		SERVER_SETMSG(ER_VARCHAR_TO_TEXT_LEN, "Set column \'%-.192s\' to TEXT type.");
		SERVER_SETMSG(ER_CHAR_TO_VARCHAR_LEN, "Set column \'%-.192s\' to VARCHAR type.");
		SERVER_SETMSG(ER_KEY_COLUMN_DOES_NOT_EXITS, "Key column \'%-.192s\' doesn\'t exist in table.");
		SERVER_SETMSG(ER_INC_INIT_ERR, "Set auto-increment initialize value to 1.");
		SERVER_SETMSG(ER_WRONG_ARGUMENTS, "Incorrect arguments to %s.");
		SERVER_SETMSG(ER_SET_DATA_TYPE_INT_BIGINT, "Set auto-increment data type to int or bigint.");
		SERVER_SETMSG(ER_TIMESTAMP_DEFAULT, "Set default value for timestamp column \'%-.64s\'.");
		SERVER_SETMSG(ER_CHARSET_ON_COLUMN, "Cannot set charset on column \'%-.64s\' in table \'%-.64s\'.");
		SERVER_SETMSG(ER_AUTO_INCR_ID_WARNING, "Auto increment column \'%-.64s\' is meaningful? it's dangerous!");
		SERVER_SETMSG(ER_ALTER_TABLE_ONCE, "Merge the alter statement for table \'%-.64s\' to ONE.");
		SERVER_SETMSG(ER_BLOB_CANT_HAVE_DEFAULT, "BLOB/TEXT column \'%-.192s\' can\'t have a default value.");
		SERVER_SETMSG(ER_END_WITH_SEMICOLON, "Add \';\' after the last sql statement.");
		SERVER_SETMSG(ER_NON_UNIQ_ERROR, "Column \'%-.192s\' in %-.192s is ambiguous.");
		SERVER_SETMSG(ER_TABLE_NOT_EXISTED_ERROR, "Table \'%-.192s\' doesn't exist.");
		SERVER_SETMSG(ER_UNKNOWN_TABLE, "Unknown table \'%-.192s\' in %-.32s.");
		SERVER_SETMSG(ER_INVALID_GROUP_FUNC_USE, "Invalid use of group function.");
		SERVER_SETMSG(ER_INDEX_USE_ALTER_TABLE, "Use Alter table statement to create index instead.");
		SERVER_SETMSG(ER_WITH_DEFAULT_ADD_COLUMN, "Set Default value for column \'%-.192s\' in table \'%-.192s\'");
		SERVER_SETMSG(ER_TRUNCATED_WRONG_VALUE, "Truncated incorrect %-.32s value: \'%-.128s\'");
		SERVER_SETMSG(ER_TEXT_NOT_NULLABLE_ERROR, "TEXT/BLOB Column \'%-.64s\' in table \'%-.64s\' can't  been not null.");
		SERVER_SETMSG(ER_WRONG_VALUE_FOR_VAR, "Variable \'%-.64s\' can\'t be set to the value of \'%-.200s\'");
		SERVER_SETMSG(ER_TOO_MUCH_AUTO_TIMESTAMP_COLS, "Incorrect table definition; there can be only one TIMESTAMP column with CURRENT_TIMESTAMP in DEFAULT or ON UPDATE clause");
		SERVER_SETMSG(ER_INVALID_ON_UPDATE, "Invalid ON UPDATE clause for \'%-.192s\' column");
		SERVER_SETMSG(ER_DDL_DML_COEXIST, "DDL can not coexist with the DML for table \'%-.192s\'.");
		SERVER_SETMSG(ER_SLAVE_CORRUPT_EVENT, "Corrupted replication event was detected.");
		SERVER_SETMSG(ER_COLLATION_CHARSET_MISMATCH, "COLLATION \'%s\' is not valid for CHARACTER SET \'%s\'");
		SERVER_SETMSG(ER_NOT_SUPPORTED_ALTER_OPTION, "Not supported statement of alter option");
		SERVER_SETMSG(ER_CONFLICTING_DECLARATIONS, "Conflicting declarations: \'%s%s\' and \'%s%s\'");
		SERVER_SETMSG(ER_IDENT_USE_KEYWORD, "Identifier \'%s\' is keyword in MySQL.");
		SERVER_SETMSG(ER_VIEW_SELECT_CLAUSE, "View\'s SELECT contains a \'%s\' clause");
		SERVER_SETMSG(ER_OSC_KILL_FAILED, "Can not find OSC executing task");
		SERVER_SETMSG(ER_NET_PACKETS_OUT_OF_ORDER, "Got packets out of order");
		SERVER_SETMSG(ER_NOT_SUPPORTED_ITEM_TYPE, "Not supported expression type \'%s\'.");
		SERVER_SETMSG(ER_INVALID_IDENT, "Identifier \'%s\' is invalid, valid options: [a-z|A-Z|0-9|_].");
		SERVER_SETMSG(ER_INCEPTION_EMPTY_QUERY, "Inception error, Query was empty.");
		SERVER_SETMSG(ER_PK_COLS_NOT_INT, "Primary key column \'%s\' is not int or bigint type in table \'%s\'.\'%s\'.");
		SERVER_SETMSG(ER_PK_TOO_MANY_PARTS, "Too many primary key part in table \'%s\'.\'%s\', max parts: %d");
		SERVER_SETMSG(ER_REMOVED_SPACES, "Leading spaces are removed from name \'%s\'");
		SERVER_SETMSG(ER_ERROR_LAST, "TheLastError,ByeBye");
	}

	/* Register messages for use with my_error(). */
	if (my_error_register(get_server_errmsgs, ER_ERROR_FIRST, ER_ERROR_LAST))
	{
		my_free(server_errmsgs);
		DBUG_RETURN(TRUE);
	}

	init_myfunc_errs();			/* Init myfunc messages */
	DBUG_RETURN(FALSE);
}

/**
Initiates error-messages used by my_func-library.
*/

static void init_myfunc_errs()
{
	init_glob_errs();			/* Initiate english errors */
	if (!(specialflag & SPECIAL_ENGLISH))
	{
		EE(EE_FILENOTFOUND)   = ER(ER_FILE_NOT_FOUND);
		EE(EE_CANTCREATEFILE) = ER(ER_CANT_CREATE_FILE);
		EE(EE_READ)           = ER(ER_ERROR_ON_READ);
		EE(EE_WRITE)          = ER(ER_ERROR_ON_WRITE);
		EE(EE_BADCLOSE)       = ER(ER_ERROR_ON_CLOSE);
		EE(EE_OUTOFMEMORY)    = ER(ER_OUTOFMEMORY);
		EE(EE_DELETE)         = ER(ER_CANT_DELETE_FILE);
		EE(EE_LINK)           = ER(ER_ERROR_ON_RENAME);
		EE(EE_EOFERR)         = ER(ER_UNEXPECTED_EOF);
		EE(EE_CANTLOCK)       = ER(ER_CANT_LOCK);
		EE(EE_DIR)            = ER(ER_CANT_READ_DIR);
		EE(EE_STAT)           = ER(ER_CANT_GET_STAT);
		EE(EE_GETWD)          = ER(ER_CANT_GET_WD);
		EE(EE_SETWD)          = ER(ER_CANT_SET_WD);
		EE(EE_DISK_FULL)      = ER(ER_DISK_FULL);
	}
}
