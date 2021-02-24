<?php

try {
  // open a temporary file to be used during content processing
  $tmpFile = tempnam(sys_get_temp_dir(), 'phpgpio');
  $handle = fopen($tmpFile, 'w');
  assert(
    is_resource($handle),
    new RuntimeException('Failed to open temporary file!')
  );

  // hold a reference to the script name
  $self = basename($argv[0]);

  // write stub header
  fileHeader($handle);
  $di = new DirectoryIterator(__DIR__);
  foreach ($di as $item) {
    // ensure that the current item is a file
    if ($item->isFile() === false) {
      continue;
    }

    // ensure that the current item is not this script
    if ($item->getFilename() === $self) {
      continue;
    }

    // extract item's content
    $content = file($item->getPathname(), FILE_IGNORE_NEW_LINES);

    // write content to stub
    fileContent($handle, $content);
  }

  // close temporary file
  fclose($handle);

  // move temporary file to final stub file
  assert(
    rename($tmpFile, __DIR__ . '/../phpgpio.stub.php'),
    new RuntimeException('Failed to write stub file!')
  );
} catch (Exception $exception) {
  echo 'Error! ', $exception->getMessage(), PHP_EOL;
}

function fileHeader($stub): void {
  fwrite($stub, '<?php');
  fwrite($stub, "\n\n");
  fwrite($stub, '/** @generate-function-entries */');
  fwrite($stub, "\n\n");
  fwrite($stub, 'namespace GPIO;');
  fwrite($stub, "\n\n");
}

function fileContent($stub, array $content): void {
  $lines  = count($content);
  $marker = false;
  for ($i = 0; $i < $lines; $i++) {
    if (strpos($content[$i], 'namespace') !== false) {
      $marker = true;

      continue;
    }

    if ($marker && $content[$i] !== '') {
      break;
    }
  }

  fwrite($stub, implode("\n", array_slice($content, $i)));
  fwrite($stub, "\n");
}
