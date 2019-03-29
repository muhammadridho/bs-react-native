open Node;
open Belt;

[@bs.module "mkdirp"] external mkdirpSync: string => unit = "sync";

let namespace = "BsReactNative";
let root = Process.cwd();
let sourcePath = Path.join([|root, "build/odoc-html"|]);
let outputPath = Path.join([|root, "build/intermediate"|]);

type file = {
  name: string,
  content: string,
};

let get = (globPattern: string) => {
  globPattern
  ->Glob.glob
  ->Future.mapOk(SortArray.String.stableSort)
  ->Future.mapOk(Array.reverse)
  ->Future.mapOk(files =>
      files->Array.map(item =>
        {name: item, content: Fs.readFileAsUtf8Sync(item)}
      )
    );
};

let shortenFilenames = files => {
  files->Array.map(file =>
    {...file, name: file.name |> Js.String.replace(sourcePath, "")}
  );
};

let filterDuplicatedFilesWithNamespace = files => {
  files->Array.keep(file =>
    !(file.name |> Js.String.includes("-" ++ namespace ++ "/"))
  );
};

let splitMark = "</code></h1>";
let toRemove = "</body></html>";
let transform = files => {
  files->Array.reduce(
    [||],
    (files, file) => {
      let splittedContent = file.content |> Js.String.split(splitMark);
      let content = splittedContent[1];
      if (content->Option.isNone) {
        Js.log2(file.name, "can't be transformed");
      };
      content
      ->Option.map(content
          // remove end of html + fixup broken <header>
          =>
            "<div>"
            ++ (content |> Js.String.replace(toRemove, ""))
            |> Js.String.replace("</header>", "</div>")
          )
      ->Option.map(content => files->Array.concat([|{...file, content}|]))
      ->Option.getWithDefault(files);
    },
  );
};

let write = files => {
  files->Array.forEach(file => {
    let filename =
      Path.join([|
        outputPath,
        file.name |> Js.String.replace("/" ++ namespace, "docs"),
      |]);
    mkdirpSync(Path.dirname(filename));
    Fs.writeFileAsUtf8Sync(filename, file.content);
  });
};

Path.join([|sourcePath, "**/*.html"|])
->get
->Future.map(files => files->Result.getExn)
->Future.map(shortenFilenames)
->Future.map(filterDuplicatedFilesWithNamespace)
->Future.map(transform)
->Future.map(write);
