#include "semantichighlighting.h"

SemanticHighlighting::SemanticHighlighting(QObject *parent)
	: QLanguageServerModule{parent}
{

}

QString SemanticHighlighting::name() const {
	return "Semantichighlighting";
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {

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
