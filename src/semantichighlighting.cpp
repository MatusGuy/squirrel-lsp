#include "semantichighlighting.h"

QString SemanticHighlighting::name() const {
	return "SemantichHighlighting";
}

void SemanticHighlighting::semanticTokensRequest(const QByteArray &,
												 const SemanticTokensParams & params,
												 LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
																	SemanticTokensPartialResult>&& resp) {
	QString docpath = QUrl(params.textDocument.uri).toLocalFile();

	auto reader = SquirrelReader::read(docpath);
	if (!reader->good()) {
		delete reader;
		return;
	}

	SemanticTokens tokens;
	int deltaline = 1;
	int deltastart = 0;
	for (auto token : reader->tokens()) {
		Logger::info(QString("old deltaline: %1").arg(deltaline));
		Logger::info(QString("token.first.start.line: %1").arg(token.first.start.line));
		deltaline = qMax(token.first.start.line - 1 - deltaline, 0);
		//Logger::info(QString("new deltaline: %1").arg(deltaline));
		deltastart = token.first.start.character - deltastart;

		//protocol()->notifyShowMessage({MessageType::Info, QString("%1 %2").arg(deltaline).arg(type).toUtf8()});

		tokens.data.append(deltaline); // line
		tokens.data.append(deltastart); // startChar
		tokens.data.append(token.first.end.character - token.first.start.character); // length
		tokens.data.append(static_cast<int>(token.second)); // tokenType
		tokens.data.append(0); // tokenModifiers
	}

	resp.sendResponse(tokens);

	delete reader;
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
