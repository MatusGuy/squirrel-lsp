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
	SQVM vm(nullptr, 1024);
	vm.Init()
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {
	protocol->registerSemanticTokensRequestHandler(semanticTokensRequest);
}

void SemanticHighlighting::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.semanticTokensProvider = SemanticTokensOptions{
		true,
		SemanticTokensLegend{
			SEMANTIC_TOKEN_NAMES,
			{}
		},
		false,
		true
	};
}
