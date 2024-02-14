#include "semantichighlighting.h"

QString SemanticHighlighting::name() const {
	return "SemantichHighlighting";
}

void SemanticHighlighting::semanticTokensRequest(const QByteArray &,
												 const SemanticTokensParams & params,
												 LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
																	SemanticTokensPartialResult>&& resp) {
	QString docpath = QUrl(params.textDocument.uri).toLocalFile();

	/*
	auto reader = SquirrelReader::read(docpath);
	if (!reader->good()) {
		delete reader;
		return;
	}
	*/

	QFile file(docpath);

	// Open the file in ReadOnly mode
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		// Report an error if the file couldn't be opened
		Logger::error(QString("Error opening file: %1").arg(file.errorString()));
		//m_good = false;
		return;
	}

	// Create a QTextStream to read from the file
	QTextStream in(&file);

	// Read all text from the file
	QString content = in.readAll();

	// Check for errors during reading
	if (in.status() != QTextStream::Ok) {
		Logger::error(QString("Error reading file: %1").arg(in.status()));
		//m_good = false;
		return;
	}

	SemanticTokens tokens;
	int lastline = 0;
	int lastchar = 0;
	for (auto token : SquirrelReader::get().lex(content)) {
		auto semtk = lextkToSemtk(token.second);
		if (!semtk.has_value()) {
			continue;
		}
		int type = static_cast<int>(semtk.value());

		int deltaline = qMax(token.first.line-1 - lastline, 0);

		int deltastart;
		if (deltaline == 0) {
			// We're in the same line.
			deltastart = qMax(token.first.start - lastchar, 0);
		} else {
			// We're in a different line, don't use delta.
			deltastart = token.first.start;
		}

		//protocol()->notifyShowMessage({MessageType::Info, QString("%1 %2").arg(deltaline).arg(type).toUtf8()});

		tokens.data.append(deltaline); // line
		tokens.data.append(deltastart); // startChar
		tokens.data.append(token.first.end - token.first.start); // length
		tokens.data.append(type); // tokenType
		tokens.data.append(0); // tokenModifiers

		lastline = token.first.line-1;
		lastchar = token.first.start;
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
