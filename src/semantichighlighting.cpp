#include "semantichighlighting.h"

QString SemanticHighlighting::name() const {
	return "SemantichHighlighting";
}

void SemanticHighlighting::semanticTokensRequest(const QByteArray &,
												 const SemanticTokensParams & params,
												 LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
																	SemanticTokensPartialResult>&& resp) {
	QString docpath = QUrl(params.textDocument.uri).toLocalFile();
	//Logger::get().log(MessageType::Info, QString("Opening %1").arg(docpath).toUtf8());

	//protocol()->notifyShowMessage({MessageType::Info, "Process semantic tokens request."});

	QFile doc(docpath);

	// Open the file in ReadOnly mode
	if (!doc.open(QIODevice::ReadOnly | QIODevice::Text)) {
		// Report an error if the file couldn't be opened
		Logger::get().log(MessageType::Error, QString("Error opening file: %1").arg(doc.errorString()));
		return;
	}

	// Create a QTextStream to read from the file
	QTextStream in(&doc);

	// Read all text from the file
	QString fileContent = in.readAll();

	// Check for errors during reading
	if (in.status() != QTextStream::Ok) {
		Logger::get().log(MessageType::Error, QString("Error reading file: %1").arg(in.status()));
		doc.close(); // Close the file before returning
		return;
	}

	// Close the file after reading
	doc.close();

	QList<QPair<SquirrelEnv::Range, SQInteger>> lexed = SquirrelEnv::get().lex(fileContent);

	SemanticTokens tokens;
	int deltaline = 1;
	int deltastart = 0;
	for (auto token : lexed) {
		auto semtk = lextkToSemtk(token.second);
		if (!semtk.has_value()) continue;
		int type = static_cast<int>(semtk.value());

		//Logger::get().log(MessageType::Info, QString("old deltaline: %1").arg(deltaline));
		//Logger::get().log(MessageType::Info, QString("token.first.line: %1").arg(token.first.line));
		deltaline = qMax(token.first.line - 1 - deltaline, 0);
		//Logger::get().log(MessageType::Info, QString("new deltaline: %1").arg(deltaline));
		deltastart = token.first.start - deltastart;

		//protocol()->notifyShowMessage({MessageType::Info, QString("%1 %2").arg(deltaline).arg(type).toUtf8()});

		tokens.data.append(deltaline); // line
		tokens.data.append(deltastart); // startChar
		tokens.data.append(token.first.end - token.first.start); // length
		tokens.data.append(type); // tokenType
		tokens.data.append(0); // tokenModifiers
	}

	resp.sendResponse(tokens);
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {
	LanguageServerModule::registerHandlers(server, protocol);

	protocol->registerSemanticTokensRequestHandler(REQ_HANDLER(SemanticHighlighting::semanticTokensRequest, _1, _2 ,_3));
}

void SemanticHighlighting::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.semanticTokensProvider = SemanticTokensOptions{
		false,
		SemanticTokensLegend{SEMANTIC_TOKEN_TYPES,{}},
		false,
		true
	};
}
