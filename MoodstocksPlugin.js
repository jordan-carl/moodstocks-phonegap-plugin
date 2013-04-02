var MoodstocksPlugin = {

    // Callback validator
    callbackValidator: function(name, cb) {
        if(!cb) {
            return function() {};
        }

        if(typeof cb != "function") {
            return function() {
                console.log(name + " callback parameter must be a function!");
            };
        }

        return cb;
    },

    // Load scanner with given api key & api secret pair
    open: function(success, fail) {

        success = this.callbackValidator("open success", success);
        fail = this.callbackValidator("open fail", fail);

        return cordova.exec(success, fail, "MoodstocksPlugin","open", []);
    },

    // Sync the cache
    sync: function(isReady, inProgress, finished, fail) {

        isReady = this.callbackValidator("sync isReady", isReady);
        inProgress = this.callbackValidator("sync inProgress", inProgress);
        finished = this.callbackValidator("sync finished", finished);
        fail = this.callbackValidator("sync fail", fail);

        function successWrapper(result) {
            switch(result.status) {
                case 1:
                    isReady.call(null);
                    break;
                case 2:
                    inProgress.call(null, result.progress);
                    break;
                case 3:
                    finished.call(null);
                    break;
                case 0:
                    fail.call(null, result.message);
                    break;
                default:
                    break;
            }
        }

        return cordova.exec(successWrapper, fail, "MoodstocksPlugin", "sync", []);
    },

    // Launch the scanner
    scan: function(success, cancel, fail, scanOptions) {
        // Scan formats
        var scanFormats = {
            ean8: 1 << 0,                /* EAN8 linear barcode */
            ean13: 1 << 1,               /* EAN13 linear barcode */
            qrcode: 1 << 2,              /* QR Code 2D barcode */
            dmtx: 1 << 3,                /* Datamatrix 2D barcode */
            image: 1 << 31               /* Image match */
        }

        var resultFormats = {
            none: "None",
            ean8: "EAN8",
            ean13: "EAN13",
            qrcode: "QR CODE",
            dmtx: "DATA MATRIX",
            image: "IMAGE"
        }

        success = this.callbackValidator("scan success", success);
        cancel = this.callbackValidator("scan cancel", cancel);
        fail = this.callbackValidator("scan fail", fail);

        // Wrap the success callback with scan result's type and value
        function successWrapper(result) {
            for (strFormat in scanFormats) {
                if (result.format === scanFormats[strFormat]) {
                    success.call(null, resultFormats[strFormat], result.value);
                    return;
                }
            }
            cancel.call(null);
        }

        if (!scanOptions) {
            scanOptions = {image: true};
        }

        var formats = 0;
        // Set the scan options according to the user choices
        for (strFormat in scanFormats) {
            if (scanOptions[strFormat]) {
                formats |= scanFormats[strFormat];
            }
        }

        return cordova.exec(successWrapper, fail, "MoodstocksPlugin", "scan", [formats]);
    },

    // pause the scan session
    pause: function(success, fail) {

        success = this.callbackValidator("pause success", success);
        fail = this.callbackValidator("pause fail", fail);

        return cordova.exec(success, fail, "MoodstocksPlugin", "pause", []);
    },

    // resume the scan session
    resume: function(success, fail) {

        success = this.callbackValidator("resume success", success);
        fail = this.callbackValidator("resume fail", fail);

        return cordova.exec(success, fail, "MoodstocksPlugin", "resume", []);
    },

    // dismiss the scanner
    dismiss: function(success, fail) {

        success = this.callbackValidator("dismiss success", success);
        fail = this.callbackValidator("dismiss fail", fail);

        return cordova.exec(success, fail, "MoodstocksPlugin", "dismiss", []);
    }
}
