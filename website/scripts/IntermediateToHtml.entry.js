const moduleAlias = require("module-alias");
moduleAlias.addAliases({
  "react-native": require.resolve("react-native-web"),
});
moduleAlias();

require("./IntermediateToHtml.bs.js");
