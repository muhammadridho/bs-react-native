open Node;
open Belt;

[@bs.module "mkdirp"] external mkdirpSync: string => unit = "sync";

let namespace = "BsReactNative";
let root = Process.cwd();
let sourcePath = Path.join([|root, "build/intermediate"|]);
let outputPath = Path.join([|root, "dist"|]);

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
let transform = files => {
  files->Array.map(file => {
    let content = Prerender.page(file.name, file.content);
    {...file, content};
  });
};

let write = files => {
  files->Array.forEach(file => {
    let filename =
      Path.join([|
        outputPath,
        file.name |> Js.String.replace(sourcePath, ""),
      |]);
    mkdirpSync(Path.dirname(filename));
    Fs.writeFileAsUtf8Sync(filename, file.content);
  });
};

Path.join([|sourcePath, "**/*.html"|])
->get
->Future.map(files => files->Result.getExn)
->Future.map(transform)
->Future.map(write);
