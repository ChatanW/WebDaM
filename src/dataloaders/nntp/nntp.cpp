#include "nntp.hpp"

namespace dl {

NNTP::NNTP()
{
	defaultSchema = new(ModelSchema);
	defaultSchema->addKey("group", "string");
	defaultSchema->addKey("header", "string");
	defaultSchema->addKey("body", "string");
}

DataLoaderInfo * init_internal(DataContainer * dc, std::string source, std::string user, std::string pwd)
{
	int key;
	nntp::nntp conn;
	std::string mname, group, header, body, msgid, rep;
	DataLoaderInfo *res = new(DataLoaderInfo);
	
	if (user && pwd) {
		if (!conn->secureConnect(source) || !conn->connect(source) || !conn->login(user, pwd))
			throw(connect_exception());
	}
	else {
		if (!conn->connect(source))
			throw(connect_exception());
	}
	
	res->name = "nntp_" + dc->newKey();
	res->dc = dc;
	res->source = source;
	res->loader_name = "NNTP";
	
	dc->newModel(res->name, defaultSchema);
	dc->newLoader(res);
	
	if (conn->process_command("LIST") / 100 == 2) {
		while(conn->read_multiline(group)) {
			group = group.substr(0, group.find_first_of(' '));
			if (conn->process_command("LISTGROUP " + group) / 100 == 2) {
				while(conn->read_multiline(msgid)) {
					header = body = "";
					if (conn->process_command("HEADER " + msgid) / 100 == 2)
						while(conn->read_multiline(rep)) { header += rep; rep = ""; }
					if (conn->process_command("BODY " + msgid) / 100 == 2)
						while(conn->read_multiline(rep)) { body += rep; rep = ""; }
					key = dc->getNewKey(res->name);
					dc->updateKey(res->name, key, "group", group);
					dc->updateKey(res->name, key, "header", header);
					dc->updateKey(res->name, key, "body", body);
				}
			}
		}
	}
	return res;
}

DataLoaderInfo * NNTP::init(DataContainer *dc, std::string source)
{
	return(init_internal(dc, source, NULL, NULL));
}

DataLoaderInfo * NNTP::init(DataContainer *dc, std::string source, std::string user, std::string pwd)
{
	return(init_internal(dc, source, user, pwd));
}

int update(DataLoaderInfo * info) {
	(void) info;
	
	return 0;
}

int update(DataLoaderInfo * info, std::string user, std::string pwd) {
	(void) info;
	(void) user;
	(void) pwd;
	
	return 0;
}
