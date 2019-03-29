let page = (name, content) => {
  let header = ReactDOMServerRe.renderToString(<AppHeader />);
  header ++ content;
};
