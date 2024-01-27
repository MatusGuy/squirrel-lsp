#include "semantichighlighting.h"

SemanticHighlighting::SemanticHighlighting(QObject *parent)
	: QLanguageServerModule{parent}
{

}

QString SemanticHighlighting::name() const {
	return "SemantichHighlighting";
}

void SemanticHighlighting::semanticTokensRequest(const QByteArray &,
												 const SemanticTokensParams & params,
												 LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
																	SemanticTokensPartialResult>&& resp) {
	QString docpath(params.textDocument.uri);
	QFile doc(docpath);
	doc.open(QFile::ReadOnly);

	QList<QPair<SquirrelEnv::Range, SQInteger>> lexed = SquirrelEnv::get().lex(doc.readAll());
	doc.close();

	SemanticTokens tokens;
	int deltaline = 0;
	int deltastart = 0;
	for (auto token : lexed) {
		auto semtk = lextkToSemtk(token.second);
		if (!semtk.has_value()) continue;
		int type = static_cast<int>(semtk.value());

		deltaline = token.first.line - deltaline;
		deltastart = token.first.start - deltastart;

		tokens.data.append(deltaline); // line
		tokens.data.append(deltastart); // startChar
		tokens.data.append(token.first.start - token.first.end); // length
		tokens.data.append(type); // tokenType
		tokens.data.append(0); // tokenModifiers
	}


	resp.sendResponse(tokens);
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {

	protocol->registerSemanticTokensRequestHandler(semanticTokensRequest);
	protocol->notifyShowMessage({MessageType::Info, "Hello!"});
}

void SemanticHighlighting::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.semanticTokensProvider = SemanticTokensOptions{
		false,
		SemanticTokensLegend{{},{}},
		false,
		true
	};
}
